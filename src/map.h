#ifndef MAP_H
#define MAP_H
#include <vector>
#include "map_object.h"
#include <string>

class Map {
    public:
        Map(std::string filename);
        ~Map();
        Map *load_map(std::string filename);
        int width;
        int height;
        std::vector<std::vector<MapObject*>> map;
        void get_objects(int x, int y, char type);
        std::pair<int, int> get_pacman_index();
        std::vector<std::pair<int, int>> get_ghosts_indexes();
        std::vector<std::pair<int, int>> get_keys_indexes();
        std::pair<int, int> get_portal_index();
        std::string filename;

    private:
        std::vector<std::pair<int, int>> keys;
        std::vector<std::pair<int, int>> ghosts;
        std::pair<int, int> pacman;
        std::pair<int, int> end;

};


#endif // MAP_H
