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
        exit(1); // debug TODO: vyriesit bez exitu
    }
    std::string line;
    std::getline(input, line);
    char *number = strtok((char*)line.c_str(), " ");
    int width = atoi(number);
    number = strtok(NULL, " ");
    int height = atoi(number);
    // TODO: skraslit 
    std::cout << "width: " << width << std::endl;
    std::cout << "height: " << height << std::endl;
    std::vector<std::vector<MapObject>> map;
    while (std::getline(input, line)) {
        std::cout << line << std::endl;
        std::vector<MapObject> row;
        for (int i = 0; i < line.length(); i++) {
            MapObject object(line[i], i, map.size());
            row.push_back(object);
        }
        map.push_back(row);

    }
    // debug print
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            if (map[i][j].is_static()) {
                std::cout << map[i][j].static_object << " ";
            } 
            else {
                std::cout << map[i][j].dynamic_object[0] << " ";
            }
        }
        std::cout << std::endl;
    }
    input.close();

}


