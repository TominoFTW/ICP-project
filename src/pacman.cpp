#include <tuple>
#include "map_object.h"
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QBrush>
#include <QColor>
#include <QPen>
#include <QGraphicsItem>
#include "map_grid.h"
#include "pacman.h"
#include "map.h"
#include <iostream>
Pacman::Pacman(int x, int y, Map &map){
    this->direction = 0;
    this->position = std::make_tuple(x*50, y*50);
    this->setBrush(Qt::yellow);
    this->setRect(0,0,50,50);
    this->setPos(std::get<0>(this->position), std::get<1>(this->position));

    
}

void Pacman::move(int direction, QGraphicsScene &scene, Map &map){
    switch(direction){
        case 0:
            std::get<0>(this->position) += 50;
            std::cout << std::get<0>(this->position)<< " " << std::get<1>(this->position) << std::endl;
            if (map.map[std::get<1>(this->position)/50][std::get<0>(this->position)/50].is_free()){
                this->setPos(std::get<0>(this->position), std::get<1>(this->position));
            }
            else{
                std::get<0>(this->position) -= 50;
            }

            break;
        case 1:
            std::get<1>(this->position) += 50;
            std::cout << std::get<0>(this->position)<< " " << std::get<1>(this->position) << std::endl;
            if (map.map[std::get<1>(this->position)/50][std::get<0>(this->position)/50].is_free()){
                this->setPos(std::get<0>(this->position), std::get<1>(this->position));
            }
            else{
                std::get<1>(this->position) -= 50;
            }

            break;
        case 2:
            std::get<0>(this->position) -= 50;
            std::cout << std::get<0>(this->position)<< " " << std::get<1>(this->position) << std::endl;
            if (map.map[std::get<1>(this->position)/50][std::get<0>(this->position)/50].is_free()){
                this->setPos(std::get<0>(this->position), std::get<1>(this->position));
            }
            else{
                std::get<0>(this->position) += 50;
            }


            break;
        case 3:
            std::get<1>(this->position) -= 50;
            std::cout << std::get<0>(this->position)<< " " << std::get<1>(this->position) << std::endl;
            if (map.map[std::get<1>(this->position)/50][std::get<0>(this->position)/50].is_free()){
                this->setPos(std::get<0>(this->position), std::get<1>(this->position));
            }
            else{
                std::get<1>(this->position) += 50;
            }


            break;
    }
}