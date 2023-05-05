#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "map.h"
#include "map_object.h"
#include <cstring>


Map::Map(std::string filename) {
    std::ifstream input;
    input.open(filename);
    if (!input) {
        std::cout << "Unable to open file";
        return;
    }
    this->filename = filename;
    std::string line;
    std::getline(input, line);
    char *number = strtok((char*)line.c_str(), " ");
    this->width = atoi(number);
    number = strtok(NULL, " ");
    this->height = atoi(number);
    // TODO: skraslit 
    std::cout << width << ' ' << height << std::endl;
    while (std::getline(input, line)) {
        std::cout << line << std::endl;
        std::vector<MapObject*> row;
        MapObject *xy = new MapObject('X');
        row.push_back(xy);
        for (int i = 0; i < line.length(); i++) {
            
            MapObject *object = new MapObject(line[i]);
            get_objects(i+1, this->map.size()+1, line[i]);
            row.push_back(object);
        }
        MapObject *x = new MapObject('X');
        row.push_back(x);
        this->map.push_back(row);

    }
    std::vector<MapObject*>* top_row = new std::vector<MapObject*>();
    for (int i = 0; i < map[0].size(); i++) {
        MapObject* obj = new MapObject('X');
        top_row->push_back(obj);
    }
    this->map.insert(this->map.begin(), *top_row);

    std::vector<MapObject*>* bottom_row = new std::vector<MapObject*>();
    for (int i = 0; i < map[0].size(); i++) {
        MapObject* obj = new MapObject('X');
        bottom_row->push_back(obj);
    }
    this->map.push_back(*bottom_row);
    input.close();

}
Map::~Map() {
    for (int i = 0; i < this->map.size(); i++) {
        for (int j = 0; j < this->map[i].size(); j++) {
            delete this->map[i][j];
        }
    }
}
Map* Map::load_map(std::string filename) {
    return new Map(filename);
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
