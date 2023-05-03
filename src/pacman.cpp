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
#include <utility>
#include <QTimer>
#include <QObject>

Pacman::Pacman(int x, int y, Map &map, QGraphicsView *view) : view(view), direction(10){
    this->position = std::make_pair(x*50, y*50);
    this->setBrush(QBrush(QImage("./textures/pacman/pacman1.png").scaled(50,50)));
    this->setRect(0,0,50,50);
    this->setPos(this->position.first, this->position.second);
    this->movement.push_back(std::make_pair(this->position.first, this->position.second));
}

void Pacman::move(int direction, QGraphicsScene &scene, Map &map){
    switch(this->direction){
        case 0:
            //     // todo potom, co ghost odejde tak to dalsi pole dat jako dynamic a to predtim jako static?
            //     // nebo to cele predelat na static a jenom kontrolovat souradnice nekde, respektive se je naucit predavat pres map grid???
            if (map.map[this->position.second/50][(this->position.first+50)/50]->is_free()){
                this->position.first += 50;
                this->setPos(this->position.first, this->position.second);
            }
            this->movement.push_back(std::make_pair(this->position.first, this->position.second));

            break;
        case 1:
            if (map.map[(this->position.second+50)/50][this->position.first/50]->is_free()){
                this->position.second += 50;
                this->setPos(this->position.first, this->position.second);
            }
            this->movement.push_back(std::make_pair(this->position.first, this->position.second));

            break;
        case 2:
            if (map.map[this->position.second/50][(this->position.first-50)/50]->is_free()){
                this->position.first -= 50;
                this->setPos(this->position.first, this->position.second);
            }
            this->movement.push_back(std::make_pair(this->position.first, this->position.second));


            break;
        case 3:
            if (map.map[(this->position.second-50)/50][this->position.first/50]->is_free()){
                this->position.second -= 50;
                this->setPos(this->position.first, this->position.second);
            }
            this->movement.push_back(std::make_pair(this->position.first, this->position.second));


            break;
        default:
            break;
    }
}
void Pacman::set_direction(int direction){
    this->direction = direction;
}
void Pacman::pacman_end(){
    auto text = new QGraphicsTextItem("Game Over");
    this->scene()->addItem(text);
    text->hide();
    auto text2 = new QGraphicsTextItem("Press R to restart");
    this->scene()->addItem(text2);
    text->show();
    text->setPos(this->scene()->width()/2,this->scene()->height()/2);
}
