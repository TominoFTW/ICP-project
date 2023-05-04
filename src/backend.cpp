#include "backend.h"
#include <utility>
#include <random>
#include <iostream>
Backend::Backend(){
}

Map *Backend::load_map(std::string filename){
    this->map = new Map(filename);
    return this->map;
}

void Backend::pacman_move(Pacman &pacman){
    switch(pacman.direction){
        case 0:
            if (this->map->map[pacman.position.second/50][(pacman.position.first+50)/50]->is_free()){
                pacman.position.first += 50;
            }
            break;
        case 1:
            if (this->map->map[(pacman.position.second+50)/50][pacman.position.first/50]->is_free()){
                pacman.position.second += 50;
            }
            break;
        case 2:
            if (this->map->map[pacman.position.second/50][(pacman.position.first-50)/50]->is_free()){
                pacman.position.first -= 50;
            }
            break;
        case 3:
            if (this->map->map[(pacman.position.second-50)/50][pacman.position.first/50]->is_free()){
                pacman.position.second -= 50;
            }
            break;
        default:
            break;
    }
    pacman.movement.push_back(pacman.direction);
}


void Backend::ghost_move(Ghost &ghost, Pacman &pacman){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 3);
    check_collision(pacman, ghost);
    bool moved = false;
    while (!moved){
        int direction = dis(gen);
        switch(direction){
            case 0:
                if (this->map->map[ghost.position.second/50][(ghost.position.first+50)/50]->is_free()){
                    ghost.position.first += 50;
                    moved = true;
                }
                break;
            case 1:
                if (this->map->map[(ghost.position.second+50)/50][ghost.position.first/50]->is_free()){
                    ghost.position.second += 50;
                    moved = true;
                }
                break;
            case 2:
                if (this->map->map[ghost.position.second/50][(ghost.position.first-50)/50]->is_free()){
                    ghost.position.first -= 50;
                    moved = true;
                }
                break;
            case 3:
                if (this->map->map[(ghost.position.second-50)/50][ghost.position.first/50]->is_free()){
                    ghost.position.second -= 50;
                    moved = true;
                }
                break;
        }
    }
    check_collision(pacman, ghost);
    std::cout << "Update" << std::endl;
    std::cout << std::get<0>(ghost.position)<< " " << std::get<1>(ghost.position) << std::endl;
}
// todo skusit nahradit exception
void Backend::check_collision(Pacman &pacman, Ghost &ghost){
    if (ghost.position == pacman.position){
        std::cout << "Collision" << std::endl;
        throw 1;
    }
}
