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
    std::ifstream input(input_file); // TODO load of file
    parseInput(input);
    this->index = 0;

    this->pacman = new Pacman(backend->get_pacman_start(),backend->map, view);
    for (int i = 0; i < backend->get_ghosts_start().size(); i++) {
        Ghost *ghost = new Ghost(backend->get_ghosts_start()[i], view);
        this->add_ghost(*ghost);
    }
    auto end = backend->get_portal_pos();
    for (int i = 0; i < backend->get_keys_pos().size(); i++) {
        Key *key = new Key(backend->get_keys_pos()[i], backend->map);
        this->add_key(*key);
    }
    connect(backend, &Backend::p_move, this->pacman, &Pacman::move);



    // this->timer = new QTimer();
    // QObject::connect(timer, &QTimer::timeout, this, &Replay::update);
    // timer->start(300);
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
    std::cout << this->pacman_positions.size() << std::endl;
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
    // for (auto i: this->pacman_positions){
    //     std::cout << "(" << i.first << "," << i.second << "), " << std::endl;
    // }
    // for (auto i: this->ghost_positions){
    //     for (auto j: i){
    //         std::cout << "(" <<j.first << "," << j.second << "), ";
    //     }
    //     std::cout << std::endl;
    // }
}

// TODO do map.cpp a .h pridat neco na udrzovani stavu klicu -> potom vykresleni targetu ve spravnej moment
// kdyz prejdu klic, popnu ho z pole klicu a kdyz je pole klicu prazdny, tak vykreslim target
// TODO, kontrola kterej ghost ma nejvice zaznamu -> musi se pohnout jako posledni

void Replay::update_forward(){
    std::cout << "update forward" << std::endl;
    if (this->index == this->pacman_positions.size()){
        // timer->stop();
        return;
    }
    std::cout << "updated" << std::endl;
    this->pacman->move(this->pacman_positions[index]);
    // this->ghost->move(ghost_positions[index]);
    this->index++;
}

void Replay::update_backward(){
    std::cout << "update backward" << std::endl;
    if (this->index == 0){
        // timer->stop();
        return;
    }
    this->pacman->move(pacman_positions[index]);
    // this->ghost->move(ghost_positions[index]);
    this->index--;
}


void Replay::add_ghost(Ghost &ghost){
    this->ghosts.push_back(&ghost);
}
void Replay::add_key(Key &key){
    this->keys.push_back(&key);
}
