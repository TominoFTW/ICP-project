#ifndef MAP_H
#define MAP_H
#include <vector>
#include "map_object.h"

class Map {
    public:
        Map();
        int width;
        int height;
        std::vector<std::vector<MapObject>> map;

};


#endif // MAP_H