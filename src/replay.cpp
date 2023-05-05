#include "replay.h"
#include "map.h"
#include "map_object.h"
#include <cstring>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include "pacman.h"
#include "ghost.h"
#include <iostream>
#include <QTimer>
#include <QObject>
#include <utility>
#include "backend.h"
#include <fstream>
#include <string>
#include <vector>

// Replay::Replay(QGraphicsScene *scene){
Replay::Replay(QWidget *parent, QGraphicsScene *scene)
    : QGraphicsScene(parent) {
    std::ifstream input("./examples/replay01.txt"); // TODO load of file
    parseInput(input);
    //backend load map
    //gamestate pacman, keys, ghosts
    
    // this->timer = new QTimer();
    // QObject::connect(timer, &QTimer::timeout, this, &Replay::update);
    // timer->start(300);
    // for (int row = 0; row < map->map.size(); row++) {
    //     for (int col = 0; col < map->map[row].size(); col++) {
    //         map->map[row][col]->setRect(col*50, row*50, 50, 50);
    //         if (map->map[row][col]->color == Qt::black) {
    //             std::cout << "huhu" << std::endl;
    //             map->map[row][col]->setBrush(QBrush(QImage("./textures/misc/wall.png").scaled(50,50)));
    //         }
    //         else if(map->map[row][col]->color == Qt::blue) {
    //             map->map[row][col]->setBrush(QBrush(QImage("./textures/misc/targer.png").scaled(50,50)));
    //             // this->end = std::make_pair(col, row);
    //         }
    //         else if (map->map[row][col]->color == Qt::yellow) {
    //             map->map[row][col]->setBrush(QBrush(QImage("./textures/misc/key.png").scaled(50,50)));
    //             // this->keys.push_back(std::make_pair(col, row));
    //         }
    //         else if (map->map[row][col]->color == Qt::blue) {
    //             map->map[row][col]->setBrush(QBrush(QImage("./textures/misc/targer.png").scaled(50,50)));
    //         }
    //         else if (map->map[row][col]->color == Qt::green) {
    //             map->map[row][col]->setBrush(QBrush(QImage("./textures/misc/dot.png").scaled(50,50)));
    //             // this->ghosts.push_back(std::make_pair(col, row));
    //         }
    //         else{
    //             map->map[row][col]->setBrush(QBrush(QImage("./textures/misc/dot.png").scaled(50,50)));
    //             if (map->map[row][col]->color == Qt::darkYellow) {
    //                 // this->pacman = std::make_pair(col, row);
    //             }
    //         }
    //         map->map[row][col]->setPen(Qt::NoPen);
    //         this->addItem(map->map[row][col]);

    //     }
    // }
    input.close();
}

void Replay::parseInput(std::ifstream &input){
    if (!input) {
        std::cout << "Unable to open file";
        return;
    }
    std::string line;
    std::ofstream tmp("./examples/tmp.txt");
    while (std::getline(input, line)) {
        if (line == "pacman"){
            tmp.close();
            break;
        }
        tmp << line << std::endl;
        std::cout << "happy" << std::endl;
        
    }
    this->map = new Map("./examples/tmp.txt");
    std::remove("./examples/tmp.txt");
}

// TODO do map.cpp a .h pridat neco na udrzovani stavu klicu -> potom vykresleni targetu ve spravnej moment
// kdyz prejdu klic, popnu ho z pole klicu a kdyz je pole klicu prazdny, tak vykreslim target
// TODO, kontrola kterej ghost ma nejvice zaznamu -> musi se pohnout jako posledni

void Replay::update_forward(){
    if (index == pacman_positions.size()){
        // timer->stop();
        return;
    }
    std::cout << "update" << std::endl;
    this->pacman->move(pacman_positions[index]);
    this->ghost->move(ghost_positions[index]);
    index++;
}

void Replay::update_backward(){
    if (index == 0){
        // timer->stop();
        return;
    }
    std::cout << "update" << std::endl;
    this->pacman->move(pacman_positions[index]);
    this->ghost->move(ghost_positions[index]);
    index--;
}
