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
#include "ghost.h"
#include "map.h"
#include <iostream>
#include <random>
#include <utility>


Ghost::Ghost(int x, int y, Map &map){
    this->direction = 0;
    this->position = std::make_tuple(x*50, y*50);
    this->setBrush(QBrush(QImage("./textures/ghosts/ghost1.png").scaled(50,50)));
    this->setRect(0,0,50,50);
    this->setPos(std::get<0>(this->position), std::get<1>(this->position));
    
}

void Ghost::move(int id, QGraphicsScene &scene, Map &map){
    std::cout << std::get<0>(this->position)<< " " << std::get<1>(this->position) << std::endl;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 3);
    int direction = dis(gen);
    printf("%d\n", direction);
    switch(direction){
        case 0:
            if (map.map[std::get<1>(this->position)/50][(std::get<0>(this->position)+50)/50].is_free()){
                this->setPos(std::get<0>(this->position)+50, std::get<1>(this->position));
                // map.map[std::get<1>(this->position)/50][std::get<0>(this->position)/50].dynamic_object = false;
                // todo predelat na pair -> lepsi indexace
                // todo potom, co ghost odejde tak to dalsi pole dat jako dynamic a to predtim jako static?
                // nebo to cele predelat na static a jenom kontrolovat souradnice nekde, respektive se je naucit predavat pres map grid???
                std::get<0>(this->position) += 50;
            }

            break;
        case 1:
            if (map.map[(std::get<1>(this->position)+50)/50][std::get<0>(this->position)/50].is_free()){
                this->setPos(std::get<0>(this->position), std::get<1>(this->position)+50);
                std::get<1>(this->position) += 50;
            }
            break;
        case 2:
            if (map.map[std::get<1>(this->position)/50][(std::get<0>(this->position)-50)/50].is_free()){
                this->setPos(std::get<0>(this->position)-50, std::get<1>(this->position));
                std::get<0>(this->position) -= 50;
            }
            break;
        case 3:
            if (map.map[(std::get<1>(this->position)-50)/50][std::get<0>(this->position)/50].is_free()){
                this->setPos(std::get<0>(this->position), std::get<1>(this->position)-50);
                std::get<1>(this->position) -= 50;
            }
            break;
    }
    std::cout << "Update" << std::endl;
    std::cout << std::get<0>(this->position)<< " " << std::get<1>(this->position) << std::endl;
}