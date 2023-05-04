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
GameState::GameState(Pacman *pacman, QGraphicsScene *scene, Map *map) : pacman(pacman), scene(scene), map(map){
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
    this->pacman->move(0, *this->scene, *this->map);
    for (Ghost *ghost : this->ghosts){
        std::cout << "update ghost" << std::endl;
        ghost->move(0, *this->scene, *this->map, *this->pacman);
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
        this->pacman->pacman_end();
    }
    // update pacman
    // update ghosts
    // update map
    // update score
    // update lives
    // update gamestate

}
