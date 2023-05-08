/**
 * @file replay.cpp
 * @authors Behal Tomas xbehal02, Kontrik Jakub xkontr02
 * @brief Replay implementation.
 * @date 2023-05-08
 */
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
#include "main_scene.h"

Replay::Replay(QWidget *parent, MainScene *scene, std::string input_file, Backend *backend, QGraphicsView *view)
    : QGraphicsScene(parent), scene(scene), view(view) {
    // Load input file and parse it
    std::ifstream input(input_file);
    parseInput(input);

    // Initialize backend
    this->backend = backend;
    this->end = backend->get_portal_pos();
    this->index = 1;

    // Initialize pacman
    this->pacman = new Pacman(backend->get_pacman_start(),backend->map, view);
    this->pacman_num_moves = pacman_possible_moves();

    // Initialize ghosts
    for (size_t i = 0; i < backend->get_ghosts_start().size(); i++){
        Ghost *ghost = new Ghost(backend->get_ghosts_start()[i], view);
        this->add_ghost(*ghost);
    }

    // Initialize keys
    for (size_t i = 0; i < backend->get_keys_pos().size(); i++){
        Key *key = new Key(backend->get_keys_pos()[i], backend->map);
        this->add_key(*key);
    }

    // Connect signals and slots for replay
    connect(this->backend, &Backend::p_move, this->pacman, &Pacman::move);
    connect(this->backend, &Backend::moves_increment, this->scene, &MainScene::updateMovesText);
    connect(this->backend, &Backend::update_keys, this->scene, &MainScene::updateKeysText);

    // Update key counter
    emit backend->update_keys((int)this->keys.size());

    // If there are no keys, set portal to open
    if (this->keys.size() == 0)
        this->backend->map->map[this->end.second/50][this->end.first/50]->setBrush(QBrush(QImage("./textures/misc/targerOpen.png").scaled(50,50)));

    input.close();
}

void Replay::parseInput(std::ifstream &input){
    if (!input) {
        std::cout << "Unable to open file";
        return;
    }
    // Skip lines until pacman coordinates
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
    // Pacman reached the end => no more moves
    if ((size_t)this->index == this->pacman_positions.size()){
        return;
    }

    // Update pacman
    this->pacman->position = this->pacman_positions[this->index];
    emit backend->p_move(this->pacman_positions[this->index-1]);

    // If pacman moved, increment moves counter
    if (pacman->position != this->pacman_positions[this->index-1]){
        pacman->moves++;
        emit backend->moves_increment(pacman->moves);
    }

    // Update ghosts
    if (this->ghosts.size() > 0){
        for (size_t i = 0; i < this->ghosts.size(); i++){
            if ((size_t)this->index < this->ghost_positions[i].size()){
                this->ghosts[i]->old_position = this->ghosts[i]->position;
                this->ghosts[i]->position = this->ghost_positions[i][this->index];
                this->ghosts[i]->move();
            }
        }
    }

    // Update keys
    if (this->keys.size() != 0){
        for (auto key: this->keys){
            if (key->position == this->pacman->position){
                key->picked = true;
                key->update();
                this->picked_keys.push_back(key);
                keys.erase(std::remove(keys.begin(), keys.end(), key), keys.end());
            }
        }
        // Update portal
        if (this->keys.size() == 0){
            this->backend->map->map[this->end.second/50][this->end.first/50]->setBrush(QBrush(QImage("./textures/misc/targerOpen.png").scaled(50,50)));
        }
    }
    // Update key counter and index
    emit backend->update_keys((int)this->keys.size());
    this->index++;
}

void Replay::update_backward(){
    if (this->index == 1){
        update_start();
        return;
    }

    this->index--;
    if (pacman->position != this->pacman_positions[this->index-1]){
        pacman->moves--;
        emit backend->moves_increment(pacman->moves);
    }
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

    if (this->picked_keys.size() != 0){
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
    emit backend->update_keys((int)this->keys.size());
}

void Replay::update_start(){
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
            this->picked_keys.pop_back();
        }
        this->backend->map->map[this->end.second/50][this->end.first/50]->setBrush(QBrush(QImage("./textures/misc/targer.png").scaled(50,50)));
    }

    this->index = 1;
    this->pacman->moves = 0;
    emit backend->moves_increment(pacman->moves);
    emit backend->update_keys((int)this->keys.size());
}

void Replay::update_end(){
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
        for (auto pos: this->pacman_positions){
            for (auto key: this->keys){
                if (pos == key->position){
                    key->picked = true;
                    key->update();
                    this->picked_keys.push_back(key);
                    keys.erase(std::remove(keys.begin(), keys.end(), key), keys.end());
                }
            }
        }
    }
    if (this->keys.size() == 0){
        this->backend->map->map[this->end.second/50][this->end.first/50]->setBrush(QBrush(QImage("./textures/misc/targerOpen.png").scaled(50,50)));
    }
    this->pacman->moves = pacman_num_moves;
    emit backend->moves_increment(this->pacman->moves);
    emit backend->update_keys((int)this->keys.size());
    this->index = last+1;
}


void Replay::add_ghost(Ghost &ghost){
    this->ghosts.push_back(&ghost);
}
void Replay::add_key(Key &key){
    this->keys.push_back(&key);
}

int Replay::pacman_possible_moves(){
    int count = 0;
    for (size_t i = 1; i < this->pacman_positions.size(); i++) {
        if (this->pacman_positions[i-1] != this->pacman_positions[i])
            count++;
    }
    return count;
}

Replay::~Replay(){
    delete this->pacman;
    for (Ghost *ghost : this->ghosts){
        delete ghost;
    }
    for (Key *key : this->keys){
        delete key;
    }
}
