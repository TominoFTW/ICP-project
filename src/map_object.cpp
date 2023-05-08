
#include "map_object.h"
#include <QVector>
#include <iostream>
#include <QColor>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
MapObject::MapObject(char symbol){
    switch(symbol){
        case 'T':
            this->type = symbol;
            this->color = Qt::blue;
            break;
        case 'X':
            this->type = symbol;
            this->color = Qt::black;
            break;
        case 'K':
            this->type = symbol;
            this->color = Qt::yellow;
            break;
        case '.':
            this->type = symbol;
            this->color = Qt::white;
            break;
        case 'S':
            this->type = symbol;
            this->color = Qt::darkYellow;
            break;
        case 'G':
            this->type = symbol;
            this->color = Qt::green;
            break;
        default:
            throw "unknown symbol";
            break;
    }
}

bool MapObject::is_free(){
    return this->type != 'X';
}
