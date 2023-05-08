/**
 * @file map.h
 * @authors Behal Tomas xbehal02, Kontrik Jakub xkontr02
 * @brief Map header.
 * @date 2023-05-08
 */
#ifndef MAP_H
#define MAP_H
#include <vector>
#include "map_object.h"
#include <string>
/**
 * @brief The Map class is responsible for the map layout and the game objects that are static displayed.
 */
class Map {
    public:
        /**
         * @brief Construct a new Map object.
         * @param filename The path to the file containing the map layout.
         */
        Map(std::string filename);
        ~Map();

        /**
         * @brief Gets the object on the map at the given coordinates, sets private variables by given object on coordinats.
         * @param x The x coordinate of the object.
         * @param y The y coordinate of the object.
         * @param type The type of the object.
         */
        void get_objects(int x, int y, char type);

        /**
         * @brief Get the pacman indexes
         * 
         * @return std::pair<int, int> indexes of pacman
         */
        std::pair<int, int> get_pacman_index();

        /**
         * @brief Get the ghosts indexes
         * 
         * @return std::vector<std::pair<int, int>> 
         */
        std::vector<std::pair<int, int>> get_ghosts_indexes();

        /**
         * @brief Get the keys indexes
         * 
         * @return std::vector<std::pair<int, int>> 
         */
        std::vector<std::pair<int, int>> get_keys_indexes();

        /**
         * @brief Get the end index
         * 
         * @return std::pair<int, int> 
         */
        std::pair<int, int> get_portal_index();
        
        std::string filename;
        std::vector<std::vector<MapObject*>> map;
        int width;
        int height;

    private:
        std::vector<std::pair<int, int>> keys;
        std::vector<std::pair<int, int>> ghosts;
        std::pair<int, int> pacman;
        std::pair<int, int> end;

};


#endif // MAP_H
