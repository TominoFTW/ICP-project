#include "key.h"
#include <iostream>

Key::Key(int x, int y, Map *map): map(map){
    this->position = std::make_pair(x*50, y*50);
    this->picked = false;
}
void Key::pick(){
    if (!this->picked){
        this->picked = true;
        std::cout << "pick" << std::endl;
        this->map->map[this->position.second/50][this->position.first/50]->setBrush(QImage("./textures/misc/dot.png").scaled(50,50));
    }
}
