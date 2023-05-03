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
#include "pacman.h"

Ghost::Ghost(int x, int y, Map &map){
    this->direction = 0;
    this->position = std::make_pair(x*50, y*50);
    this->setBrush(QBrush(QImage("./textures/ghosts/ghost1.png").scaled(50,50)));
    this->setRect(0,0,50,50);
    this->setPos(this->position.first, this->position.second);
    
}

void Ghost::move(int id, QGraphicsScene &scene, Map &map, Pacman &pacman){
    // std::cout << std::get<0>(this->position)<< " " << std::get<1>(this->position) << std::endl;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 3);
    check_collision(scene, map, pacman);
    bool moved = false;
    while (!moved){
        int direction = dis(gen);
        switch(direction){
            case 0:
                    // todo potom, co ghost odejde tak to dalsi pole dat jako dynamic a to predtim jako static?
                    // nebo to cele predelat na static a jenom kontrolovat souradnice nekde, respektive se je naucit predavat pres map grid???
                if (map.map[this->position.second/50][(this->position.first+50)/50].is_free()){
                    this->position.first += 50;
                    moved = true;
                }
                break;
            case 1:
                if (map.map[(this->position.second+50)/50][this->position.first/50].is_free()){
                    this->position.second += 50;
                    moved = true;
                }
                break;
            case 2:
                if (map.map[this->position.second/50][(this->position.first-50)/50].is_free()){
                    this->position.first -= 50;
                    moved = true;
                }
                break;
            case 3:
                if (map.map[(this->position.second-50)/50][this->position.first/50].is_free()){
                    this->position.second -= 50;
                    moved = true;
                }
                break;
        }
        this->setPos(this->position.first, this->position.second);
    }
    check_collision(scene, map, pacman);
    std::cout << "Update" << std::endl;
    std::cout << std::get<0>(this->position)<< " " << std::get<1>(this->position) << std::endl;
}

void Ghost::check_collision(QGraphicsScene &scene, Map &map, Pacman &pacman){
    if (pacman.position == this->position){
        pacman.pacman_end();
    // todo
    }
}
