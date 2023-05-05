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
        MapObject *xy = new MapObject('X', 0, this->map.size());
        row.push_back(xy);
        for (int i = 0; i < line.length(); i++) {
            
            MapObject *object = new MapObject(line[i], i, this->map.size());
            row.push_back(object);
        }
        MapObject *x = new MapObject('X', 0, this->map.size());
        row.push_back(x);
        this->map.push_back(row);

    }
    std::vector<MapObject*>* top_row = new std::vector<MapObject*>();
    for (int i = 0; i < map[0].size(); i++) {
        MapObject* obj = new MapObject('X', 0, 0);
        top_row->push_back(obj);
    }
    this->map.insert(this->map.begin(), *top_row);

    std::vector<MapObject*>* bottom_row = new std::vector<MapObject*>();
    for (int i = 0; i < map[0].size(); i++) {
        MapObject* obj = new MapObject('X', 0, 0);
        bottom_row->push_back(obj);
    }
    this->map.push_back(*bottom_row);
    input.close();

}

Map* Map::load_map(std::string filename) {
    return new Map(filename);
}
