/**
 * @file backend.cpp
 * @authors Behal Tomas xbehal02, Kontrik Jakub xkontr02
 * @brief Implementation of backend class methods and variables.
 * Used for computing the logic of the game.
 * @date 2023-05-08
*/

#include <utility>
#include <random>
#include <iostream>
#include <utility>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "backend.h"

Backend::Backend(){
    this->map = nullptr;
}

Backend::~Backend(){
    if (this->map != nullptr){
        delete this->map;
        this->map = nullptr;
    }
}

Map *Backend::load_map(std::string filename){
    if (this->map != nullptr){
        delete this->map;
        this->map = nullptr;
    }
    this->map = new Map(filename);
    return this->map;
}

void Backend::pacman_move(Pacman &pacman){
    switch(pacman.get_direction()){
        case 0:
            if (this->map->map[pacman.position.second/50][(pacman.position.first+50)/50]->is_free()){
                std::pair<int,int> old_position = pacman.position;
                pacman.position.first += 50;
                pacman.moves++;
                // signals to notify GUI about the move
                emit p_move(old_position);
                emit moves_increment(pacman.moves);
            }
            break;
        case 1:
            if (this->map->map[(pacman.position.second+50)/50][pacman.position.first/50]->is_free()){
                std::pair<int,int> old_position = pacman.position;
                pacman.position.second += 50;
                pacman.moves++;
                emit p_move(old_position);
                emit moves_increment(pacman.moves);
            }
            break;
        case 2:
            if (this->map->map[pacman.position.second/50][(pacman.position.first-50)/50]->is_free()){
                std::pair<int,int> old_position = pacman.position;
                pacman.position.first -= 50;
                pacman.moves++;
                emit p_move(old_position);
                emit moves_increment(pacman.moves);
            }
            break;
        case 3:
            if (this->map->map[(pacman.position.second-50)/50][pacman.position.first/50]->is_free()){
                std::pair<int,int> old_position = pacman.position;
                pacman.position.second -= 50;
                pacman.moves++;
                emit p_move(old_position);
                emit moves_increment(pacman.moves);
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
    bool moved = false;
    bool collision = false;
    ghost.old_position = ghost.position;
    // check for collision before move
    collision = check_collision(pacman, ghost);
    if (collision){
        throw 1;
    }
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
    // check for collision after move
    collision = check_collision(pacman, ghost);
    emit g_move();
    if (collision){
        throw 1;
    }
}

bool Backend::check_collision(Pacman &pacman, Ghost &ghost){
    if (ghost.position == pacman.position or ghost.old_position == pacman.position){
        return true;
    }
    return false;
}

void Backend::check_win(std::pair<int, int> end, std::pair<int, int> pacman, int size){
    if (end == pacman && size == 0){
        emit win();
        throw 1;
    }
}

void Backend::pick_key(Key &key, Pacman &pacman,std::vector<Key*> &keys){
    if (key.position == pacman.position){
        key.picked = true;
        keys.erase(std::remove(keys.begin(), keys.end(), &key), keys.end());
    }
    emit update_keys((int)keys.size());
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

void Backend::get_replay_map(std::string input_file) {
    std::ifstream input(input_file);
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
    }
}
