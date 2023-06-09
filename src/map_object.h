/**
 * @file map_object.h
 * @authors Behal Tomas xbehal02, Kontrik Jakub xkontr02
 * @brief MapObject header
 * @date 2023-05-08
 */

#ifndef MAP_OBJECT_H
#define MAP_OBJECT_H
#include <vector>
#include <QColor>
#include <QGraphicsRectItem>
#include <QBrush>
#include <utility>

/**
 * @brief Class for map objects.
 * 
 */
class MapObject:public QGraphicsRectItem{
    public:
        /**
         * @brief Construct a new Map Object object
         * 
         * @param symbol type of object on map
         */
        MapObject(char symbol);

        /**
         * @brief If object is not wall.
         * 
         * @return bool Is it wall
         */
        bool is_free();

        char type; ///< Type of object on map
        QColor color; ///< Color of object on map for textures
};

#endif // MAP_OBJECT_H
