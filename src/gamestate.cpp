#include "gamestate.h"
#include <QTimer>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <iostream>
#include "ghost.h"


GameState::GameState(Pacman *pacman, QGraphicsScene *scene, Map &map) : scene(scene),pacman(pacman), map(map){
    timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, this, &GameState::update);
    timer->start(300);
}
void GameState::add_ghost(Ghost &ghost){
    this->ghosts.push_back(&ghost);
}
void GameState::set_pacman_dir(int direction){
    this->pacman->set_direction(direction);
}
void GameState::update(){
    this->pacman->move(0, *this->scene, this->map);
    std::cout << "updateAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAaa" << std::endl;
    for (Ghost *ghost : this->ghosts){
        std::cout << "update ghost" << std::endl;
        ghost->move(0, *this->scene, this->map, *this->pacman);
    }
    // update pacman
    // update ghosts
    // update map
    // update score
    // update lives
    // update gamestate

}
