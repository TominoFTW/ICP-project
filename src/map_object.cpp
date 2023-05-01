
#include "map_object.h"
#include <vector>
#include <iostream>
MapObject:: MapObject(char symbol, int x, int y){
    switch(symbol){
        case 'T':
        case 'X':
            this->static_object = symbol;
            this->x = x;
            this->y = y;
            this->mColor = Qt::black;
            break;
        case 'K':
        case '.':
            this->static_object = symbol;
            this->x = x;
            this->y = y;
            this->mColor = Qt::white;
            break;
        case 'S':
        case 'G':
            this->dynamic_object.push_back(symbol);
            this->x = x;
            this->y = y;
            break;
        default:
            std::cout << "unknown" << std::endl;
            break;
    }
}
bool MapObject::is_static(){
    return this->dynamic_object.empty();
}
bool MapObject::is_free(){
    return this->dynamic_object.empty() && this->static_object == '.';
}

QColor MapObject::getColor(){
    return this->mColor;
}