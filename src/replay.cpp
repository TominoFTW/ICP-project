#include "replay.h"
#include "map.h"
#include "map_object.h"
#include <cstring>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include "pacman.h"
#include "ghost.h"
#include <iostream>
#include <QTimer>
#include <QObject>
#include <utility>
#include "backend.h"
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

// Replay::Replay(QGraphicsScene *scene){
Replay::Replay(QWidget *parent, QGraphicsScene *scene, std::string input_file, Backend *backend, QGraphicsView *view)
    : QGraphicsScene(parent) {
    (void) scene;
    std::ifstream input(input_file);
    parseInput(input);

    this->backend = backend;
    this->end = backend->get_portal_pos();
    this->index = 1;

    this->pacman = new Pacman(backend->get_pacman_start(),backend->map, view);

    for (size_t i = 0; i < backend->get_ghosts_start().size(); i++) {
        Ghost *ghost = new Ghost(backend->get_ghosts_start()[i], view);
        this->add_ghost(*ghost);
    }

    for (size_t i = 0; i < backend->get_keys_pos().size(); i++) {
        Key *key = new Key(backend->get_keys_pos()[i], backend->map);
        this->add_key(*key);
    }
    connect(backend, &Backend::p_move, this->pacman, &Pacman::move);

    input.close();
}

void Replay::parseInput(std::ifstream &input){
    if (!input) {
        std::cout << "Unable to open file";
        return;
    }
    std::string line;
    while (std::getline(input, line)) {
        if (line == "pacman")
            break;
    }
    // pacman positions
    std::getline(input, line);
    std::istringstream iss(line);
    std::string tuple;
    while (std::getline(iss, tuple, ' ')) {
        std::istringstream tuple_iss(tuple);
        std::string first, second;
        std::getline(tuple_iss, first, ',');
        std::getline(tuple_iss, second, ' ');
        this->pacman_positions.push_back(std::make_pair(std::stoi(first), std::stoi(second)));
    }
    // ghosts positions
    for (int i; std::getline(input, line); i++){
        std::getline(input, line);
        std::istringstream iss(line);
        std::string tuple;
        std::vector<std::pair<int,int>> pos;
        while (std::getline(iss, tuple, ' ')) {
            std::istringstream tuple_iss(tuple);
            std::string first, second;
            std::getline(tuple_iss, first, ',');
            std::getline(tuple_iss, second, ' ');
            pos.push_back(std::make_pair(std::stoi(first), std::stoi(second)));
        }
        this->ghost_positions.push_back(pos);
    }
}

void Replay::update_forward(){
    if ((size_t)this->index == this->pacman_positions.size()){
        return;
    }

    this->pacman->position = this->pacman_positions[this->index];
    emit backend->p_move(this->pacman_positions[this->index-1]);

    if (this->ghosts.size() > 0){
        for (size_t i = 0; i < this->ghosts.size(); i++){
            if ((size_t)this->index < this->ghost_positions[i].size()){
                this->ghosts[i]->old_position = this->ghosts[i]->position;
                this->ghosts[i]->position = this->ghost_positions[i][this->index];
                this->ghosts[i]->move();
            }
        }
    }

    if (this->keys.size() != 0) {
        for (auto key: this->keys){
            if (key->position == this->pacman->position){
                key->picked = true;
                key->update();
                this->picked_keys.push_back(key);
                keys.erase(std::remove(keys.begin(), keys.end(), key), keys.end());
            }
        }
        if (this->keys.size() == 0){
            this->backend->map->map[this->end.second/50][this->end.first/50]->setBrush(QBrush(QImage("./textures/misc/targerOpen.png").scaled(50,50)));
        }
    }

    this->index++;
}

void Replay::update_backward(){
    if (this->index == 1){
        update_start();
        return;
    }

    this->index--;

    this->pacman->position = this->pacman_positions[this->index-1];
    this->pacman->move(pacman_positions[index]);

    if (this->ghosts.size() > 0){
        for (size_t i = 0; i < this->ghosts.size(); i++){
            if ((size_t)this->index < this->ghost_positions[i].size()) {
                this->ghosts[i]->old_position = this->ghosts[i]->position;
                this->ghosts[i]->position = this->ghost_positions[i][this->index-1];
                this->ghosts[i]->move();
            }
        }
    }

    if (this->picked_keys.size() != 0) {
        for (auto key: this->picked_keys){
            if (key->position == this->pacman_positions[this->index]){
                key->picked = false;
                key->update();
                this->keys.push_back(key);
                picked_keys.erase(std::remove(picked_keys.begin(), picked_keys.end(), key), picked_keys.end());
            }
        }
        if (this->keys.size() != 0){
            this->backend->map->map[this->end.second/50][this->end.first/50]->setBrush(QBrush(QImage("./textures/misc/targer.png").scaled(50,50)));
        }
    }
}

void Replay::update_start() {
    auto tmp = this->pacman->position;
    this->pacman->position = this->pacman_positions[0];
    emit backend->p_move(tmp);

    if (this->ghosts.size() > 0){
        for (size_t i = 0; i < this->ghosts.size(); i++){
            this->ghosts[i]->old_position = this->ghosts[i]->position;
            this->ghosts[i]->position = this->ghost_positions[i][0];
            this->ghosts[i]->move();
        }
    }

    if (this->picked_keys.size() != 0){
        for (auto key: this->picked_keys){
            key->picked = false;
            key->update();
            this->keys.push_back(key);
            picked_keys.erase(std::remove(picked_keys.begin(), picked_keys.end(), key), picked_keys.end());
        }
        this->backend->map->map[this->end.second/50][this->end.first/50]->setBrush(QBrush(QImage("./textures/misc/targer.png").scaled(50,50)));
    }
    this->index = 1;
}

void Replay::update_end() {
    auto last = this->pacman_positions.size()-1;

    auto tmp = this->pacman->position;
    this->pacman->position = this->pacman_positions[pacman_positions.size()-1];
    emit backend->p_move(tmp);

    if (this->ghosts.size() > 0){
        for (size_t i = 0; i < this->ghosts.size(); i++){
            this->ghosts[i]->old_position = this->ghosts[i]->position;
            this->ghosts[i]->position = this->ghost_positions[i][this->ghost_positions[i].size()-1];
            this->ghosts[i]->move();
            if (last < this->ghost_positions[i].size()-1) {
                last = this->ghost_positions[i].size()-1;
            }
        }
    }
    
    if (this->keys.size() != 0){
        for (auto key: this->keys){
            key->picked = true;
            key->update();
            this->picked_keys.push_back(key);
            keys.erase(std::remove(keys.begin(), keys.end(), key), keys.end());
            }
        this->backend->map->map[this->end.second/50][this->end.first/50]->setBrush(QBrush(QImage("./textures/misc/targerOpen.png").scaled(50,50)));
        }

    this->index = last+1;
}


void Replay::add_ghost(Ghost &ghost){
    this->ghosts.push_back(&ghost);
}
void Replay::add_key(Key &key){
    this->keys.push_back(&key);
}
