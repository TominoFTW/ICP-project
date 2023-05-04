#ifndef MAP_H
#define MAP_H
#include <vector>
#include "map_object.h"
#include <string>

class Map {
    public:
        Map(std::string filename);
        Map *load_map(std::string filename);
        int width;
        int height;
        std::vector<std::vector<MapObject*>> map;

};


#endif // MAP_H