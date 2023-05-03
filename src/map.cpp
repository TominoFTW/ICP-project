#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "map.h"
#include "map_object.h"
#include <cstring>


Map::Map() {
    std::ifstream input;
    input.open("examples/map-01.txt");
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
    std::cout << "width: " << width << std::endl;
    std::cout << "height: " << height << std::endl;
    while (std::getline(input, line)) {
        std::cout << line << std::endl;
        std::vector<MapObject> row;
        row.push_back(MapObject('X', 0, this->map.size()));
        for (int i = 0; i < line.length(); i++) {
            MapObject object(line[i], i, this->map.size());
            row.push_back(object);
        }
        row.push_back(MapObject('X', 0, this->map.size()));
        this->map.push_back(row);

    }
    std::vector<MapObject> top_row(map[0].size(), MapObject('X', 0, 0));
    this->map.insert(this->map.begin(), top_row);
    std::vector<MapObject> bottom_row(map[0].size(), MapObject('X', 0, 0));
    this->map.push_back(bottom_row);
    // debug print
    for (int i = 0; i < this->map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            std::cout << this->map[i][j].type << " ";
        }
        std::cout << std::endl;
    }
    input.close();

}


