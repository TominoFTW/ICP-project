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


GameState::GameState(Pacman *pacman, QGraphicsScene *scene, Map &map) : scene(scene),pacman(pacman), map(map){
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
    this->pacman->move(0, *this->scene, this->map);
    for (Ghost *ghost : this->ghosts){
        std::cout << "update ghost" << std::endl;
        ghost->move(0, *this->scene, this->map, *this->pacman);
    }
    // todo check collision moze byt aj tu ak to bude bugnute :D
    for (Key *key : this->keys){
        std::cout << "update ghaaaaaaaaaaaaaaaaaaaaaaostupdate ghost" << key->position.first <<" "<< this->pacman->position.first<< std::endl;
        if (key->position == this->pacman->position){
            key->pick();    
        }
    }
    // update pacman
    // update ghosts
    // update map
    // update score
    // update lives
    // update gamestate

}
