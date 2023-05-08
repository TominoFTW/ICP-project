/**
 * @file key.cpp
 * @authors Behal Tomas xbehal02, Kontrik Jakub xkontri02
 * @brief Key object implementation.
 * @date 2023-05-08
*/

#include <iostream>
#include "key.h"

Key::Key(std::pair<int,int> map_position, Map *map) : map(map){
    this->position = map_position;
    this->picked = false;
}

void Key::update(){
    if (!this->picked){
        this->map->map[this->position.second/50][this->position.first/50]->setBrush(QImage("./textures/misc/key.png").scaled(50,50));
    }
    else{
        this->map->map[this->position.second/50][this->position.first/50]->setBrush(QImage("./textures/misc/dot.png").scaled(50,50));
    }
}
