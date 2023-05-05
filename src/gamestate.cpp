#include "gamestate.h"
#include <QTimer>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <iostream>
#include "ghost.h"
#include "pacman.h"
#include "key.h"
#include "map.h"

//hello
GameState::GameState(Pacman *pacman, QGraphicsScene *scene, Map *map) : pacman(pacman), scene(scene), map(map), stop(false){
    this->backend = Backend();
    backend.load_map("./examples/map-01.txt");
    timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, this, &GameState::update);
    timer->start(300);
}
void GameState::add_ghost(Ghost &ghost){
    this->ghosts.push_back(&ghost);
}
void GameState::add_key(Key &key){
    this->keys.push_back(&key);
}
void GameState::set_pacman_dir(int direction){
    this->pacman->set_direction(direction);
}
void GameState::update(){
    if (stop) return;
    auto old_position = this->pacman->position;
    backend.pacman_move(*this->pacman);
    this->pacman->move(old_position);
    for (Ghost *ghost : this->ghosts){
        std::cout << "update ghost" << std::endl;
        old_position = ghost->position;
        try{
            backend.ghost_move(*ghost, *this->pacman);
        }
        catch (int e){
            std::cout << "ghost caught pacman" << std::endl;
            ghost->move(old_position);
            pacman->pacman_end();
            this->stop = true;
            return;
        }
        ghost->move(old_position);
    }
    for (Key *key : this->keys){
        backend.pick_key(*key, *this->pacman, this->keys);
        key->update();
    }
    if (this->keys.size() == 0){
        this->map->map[this->end.second/50][this->end.first/50]->setBrush(QImage("./textures/misc/targerOpen.png").scaled(50,50));
    }
    try{
        backend.check_win(this->end, this->pacman->position, this->keys.size());
    }
    catch (int e){
        pacman->pacman_win();
        this->stop = true;
        return;
    }

}
