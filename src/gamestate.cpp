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
GameState::GameState(QGraphicsView *view, Map *map) : view(view), map(map), stop(false){
    this->backend = Backend();
    backend.load_map("./examples/map-01.txt");
    // todo frontend okna vyhodit z pacmana niekam inam ???????
    this->pacman = new Pacman(backend.get_pacman_start(),map, this->view);
    for (int i = 0; i < backend.get_ghosts_start().size(); i++) {
        Ghost *ghost = new Ghost(backend.get_ghosts_start()[i], this->view);
        this->add_ghost(*ghost);
    }
    this->end = backend.get_portal_pos();
    // todo ak bude cas prerobit logiku klucov podobne ako ma pacman a ghost a iba ich schovavat ak su zobrate
    for (int i = 0; i < backend.get_keys_pos().size(); i++) {
        Key *key = new Key(backend.get_keys_pos()[i], map);
        this->add_key(*key);
    }
    timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, this, &GameState::update);
    timer->start(300);
}
GameState::~GameState(){
    delete this->pacman;
    for (Ghost *ghost : this->ghosts){
        delete ghost;
    }
    for (Key *key : this->keys){
        delete key;
    }
    delete this->timer;
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
        old_position = ghost->position;
        try{
            backend.ghost_move(*ghost, *this->pacman);
        }
        catch (int e){
            std::cout << "ghost caught pacman" << std::endl;
            ghost->move(old_position);
            pacman->pacman_end();
            this->stop = true;
            int i = 0;
            std::cout << "pacman" << std::endl;
            for (auto v : this->pacman->movement){
                std::cout << v.first << "," << v.second << " ";
            }
            this->pacman->movement.clear();
            std::cout << std::endl;
            for (Ghost *ghost : this->ghosts){
                std::cout << "ghost" << i++ << std::endl;
                for( auto v : ghost->movement){
                    std::cout << v.first << "," << v.second << " ";
                }
                std::cout << std::endl;
                ghost->movement.clear();
            }
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
        int i = 0;
        for (auto v : this->pacman->movement){
            std::cout << v.first << "," << v.second << " ";
        }
        this->pacman->movement.clear();
        std::cout << std::endl;
        for (Ghost *ghost : this->ghosts){
            std::cout << "ghost" << i++ << std::endl;
            for( auto v : ghost->movement){
                std::cout << v.first << "," << v.second << " ";
            }
            std::cout << std::endl;
            ghost->movement.clear();
        }
        return;
    }

}
