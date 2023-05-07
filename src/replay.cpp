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
    Backend *backend = new Backend();
    this->map = backend->load_map("./replays/tmp.txt");
    
    // this->timer = new QTimer();
    // QObject::connect(timer, &QTimer::timeout, this, &Replay::update);
    // timer->start(300);
    remove("./replays/tmp.txt");
    input.close();
}

void Replay::parseInput(std::ifstream &input){
    if (!input) {
        std::cout << "Unable to open file";
        return;
    }
    std::string line;
    std::ofstream tmp("./replays/tmp.txt");
    while (std::getline(input, line)) {
        if (line == "pacman"){
            tmp.close();
            break;
        }
        tmp << line << std::endl;
        std::cout << "happy" << std::endl;
        
    }
    this->ghost_positions = std::vector<std::pair<int, int>>();
    this->pacman_positions = std::vector<std::pair<int, int>>();
    // this->keys = std::vector<std::pair<int, int>>();
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
