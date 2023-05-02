
#include "map_object.h"
#include <QVector>
#include <iostream>
#include <QColor>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
MapObject:: MapObject(char symbol, int x, int y){
    switch(symbol){
        case 'T':
            this->static_object = symbol;
            this->color = Qt::blue;
            break;
        case 'X':
            this->static_object = symbol;
            this->color = Qt::black;
            break;
        case 'K':
            this->static_object = symbol;
            this->color = Qt::yellow;
            break;
        case '.':
            this->static_object = symbol;
            this->color = Qt::white;
            break;
        case 'S':
            this->dynamic_object.push_back(symbol);
            this->color = Qt::darkYellow;
            break;
        case 'G':
            this->dynamic_object.push_back(symbol);
            this->color = Qt::green;
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
