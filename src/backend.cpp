#include "backend.h"
#include <utility>
#include <random>
#include <iostream>
#include <utility>
Backend::Backend(){
    this->map = nullptr;
}
Backend::~Backend(){
    if (this->map != nullptr){
        delete this->map;
    }
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
    pacman.movement.push_back(pacman.position);
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
    ghost.movement.push_back(ghost.position);
    check_collision(pacman, ghost);
}
// todo skusit nahradit exception
void Backend::check_collision(Pacman &pacman, Ghost &ghost){
    if (ghost.position == pacman.position){
        std::cout << "Collision" << std::endl;
        throw 1;
    }
}

void Backend::check_win(std::pair<int, int> end, std::pair<int, int> pacman, int size){
    if (end == pacman && size == 0){
        std::cout << "Win" << std::endl;
        throw 1;
    }
}

void Backend::pick_key(Key &key, Pacman &pacman,std::vector<Key*> &keys){
    if (key.position == pacman.position){
        std::cout << "Key picked" << std::endl;
        key.picked = true;
        keys.erase(std::remove(keys.begin(), keys.end(), &key), keys.end());
    }
}
std::pair<int,int> Backend::get_pacman_start(){
    return this->map->get_pacman_index();
}
std::vector<std::pair<int,int>> Backend::get_ghosts_start(){
    return this->map->get_ghosts_indexes();
}
std::pair<int,int> Backend::get_portal_pos(){
    return std::make_pair(this->map->get_portal_index().first*50, this->map->get_portal_index().second*50);
}
std::vector<std::pair<int,int>> Backend::get_keys_pos(){
    std::vector<std::pair<int,int>> tmp;
    for (auto v : this->map->get_keys_indexes()){
        tmp.push_back(std::make_pair(v.first*50, v.second*50));
    }
    return tmp;
}