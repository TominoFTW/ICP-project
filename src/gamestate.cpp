#include "gamestate.h"
#include <QTimer>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <iostream>
#include "ghost.h"
#include "pacman.h"
#include "key.h"
#include "map.h"

//hello
GameState::GameState(Pacman *pacman, QGraphicsScene *scene, Map *map) : pacman(pacman), scene(scene), map(map), stop(false){
    this->backend = Backend();
    backend.load_map("./examples/map-01.txt");
    timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, this, &GameState::update);
    timer->start(300);
}
void GameState::add_ghost(Ghost &ghost){
    this->ghosts.push_back(&ghost);
}
void GameState::add_key(Key &key){
    this->keys.push_back(&key);
}
void GameState::set_pacman_dir(int direction){
    this->pacman->set_direction(direction);
}
void GameState::update(){
    if (stop) return;
    auto old_position = this->pacman->position;
    auto pos = backend.pacman_move(*this->pacman);
    this->pacman->move(old_position);
    for (Ghost *ghost : this->ghosts){
        std::cout << "update ghost" << std::endl;
        try{
            ghost->move(0, *this->scene, *this->map, *this->pacman);
        }
        catch (...){
            this->stop = true;
        }
    }
    // todo check collision moze byt aj tu ak to bude bugnute :D
    for (Key *key : this->keys){
        if (key->position == this->pacman->position){
            key->pick();   
            this->keys.erase(std::remove(this->keys.begin(), this->keys.end(), key), this->keys.end()); 
        }
    }
    // dirty todo refactor
    if (this->keys.size() == 0){
        map->map[this->end.second/50][this->end.first/50]->setBrush(QImage("./textures/misc/targerOpen.png").scaled(50,50));
    }
    if (this->pacman->position == this->end and this->keys.size() == 0){
        std::cout << "pacman end" << std::endl;
        try{
            this->pacman->pacman_end();
        }
        catch (...){
            this->stop = true;
        }
    }
    // update pacman
    // update ghosts
    // update map
    // update score
    // update lives
    // update gamestate

}
