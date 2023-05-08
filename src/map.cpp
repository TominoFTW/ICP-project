/**
 * @file map.cpp
 * @authors Behal Tomas xbehal02, Kontrik Jakub xkontr02
 * @brief Map parsing and object creation.
 * @date 2023-05-08
 */
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "map.h"
#include "map_object.h"
#include <cstring>


Map::Map(std::string filename) {
    // Open file
    std::ifstream input;
    this->filename = filename;
    input.open(filename);
    if (!input) {
        throw "Unable to open file";
    }
    // Read width and height
    std::string line;
    std::getline(input, line);
    char *number = strtok((char*)line.c_str(), " ");
    this->height = atoi(number);
    number = strtok(NULL, " ");
    this->width = atoi(number);
    
    // Read map
    while (std::getline(input, line)) {
        // Parse lines
        std::vector<MapObject*> row;
        MapObject *xy = new MapObject('X');
        row.push_back(xy);

        // Check if line is valid
        if ((int)line.length() != this->width) {
            throw "Invalid map";
        }
        for (int i = 0; i < (int)line.length(); i++) {
            MapObject *object = new MapObject(line[i]);
            get_objects(i+1, this->map.size()+1, line[i]);
            row.push_back(object);
        }
        MapObject *x = new MapObject('X');
        row.push_back(x);
        this->map.push_back(row);

    }
    
    // Add top and bottom rows
    std::vector<MapObject*>* top_row = new std::vector<MapObject*>();
    for (int i = 0; i < (int)map[0].size(); i++) {
        MapObject* obj = new MapObject('X');
        top_row->push_back(obj);
    }
    this->map.insert(this->map.begin(), *top_row);

    std::vector<MapObject*>* bottom_row = new std::vector<MapObject*>();
    for (int i = 0; i < (int)map[0].size(); i++) {
        MapObject* obj = new MapObject('X');
        bottom_row->push_back(obj);
    }
    this->map.push_back(*bottom_row);

    // Check if map is valid once more
    if ((int)this->map.size() != this->height+2) {
        throw "Invalid map";
    }

    input.close();
}

Map::~Map() {
    for (int i = 0; i < (int)this->map.size(); i++) {
        for (int j = 0; j < (int)this->map[i].size(); j++) {
            delete this->map[i][j];
        }
    }
}

void Map::get_objects(int x, int y, char type){
    switch(type){
        case 'K':
            this->keys.push_back(std::make_pair(x, y));
            break;
        case 'G':
            this->ghosts.push_back(std::make_pair(x, y));
            break;
        case 'S':
            this->pacman = std::make_pair(x, y);
            break;
        case 'T':
            this->end = std::make_pair(x, y);
            break;
        default:
            break;
    }
}

std::pair<int, int> Map::get_pacman_index(){
    return this->pacman;
}

std::pair<int, int> Map::get_portal_index(){
    return this->end;
}

std::vector<std::pair<int, int>> Map::get_ghosts_indexes(){
    return this->ghosts;
}

std::vector<std::pair<int, int>> Map::get_keys_indexes(){
    return this->keys;
}
