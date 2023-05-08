#ifndef MAP_OBJECT_H
#define MAP_OBJECT_H
#include <vector>
#include <QColor>
#include <QGraphicsRectItem>
#include <QBrush>
#include <utility>

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

        char type;
        QColor color;
};

#endif // MAP_OBJECT_H
