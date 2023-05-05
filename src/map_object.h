#ifndef MAP_OBJECT_H
#define MAP_OBJECT_H
#include <vector>
#include <QColor>
#include <QGraphicsRectItem>
#include <QBrush>
#include <utility>

class MapObject:public QGraphicsRectItem{
    public:
        MapObject(char symbol);
        char type;
        QColor color;
        bool is_free();
};

#endif // MAP_OBJECT_H
