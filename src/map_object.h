#ifndef MAP_OBJECT_H
#define MAP_OBJECT_H
#include <vector>
#include <QColor>
#include <QGraphicsRectItem>
#include <QBrush>

class MapObject:public QGraphicsRectItem{
    public:
        MapObject(char symbol, int x, int y);
        MapObject(const MapObject& other) : QGraphicsRectItem(), type(other.type), x(other.x), y(other.y), color(other.color){}
        char type;
        int x;
        int y;
        QColor color;
        bool is_free();
};

#endif // MAP_OBJECT_H
