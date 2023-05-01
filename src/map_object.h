#ifndef MAP_OBJECT_H
#define MAP_OBJECT_H
#include <vector>
#include <QColor>
#include <QGraphicsRectItem>
#include <QBrush>

class MapObject:public QGraphicsRectItem{
    public:
        MapObject(char symbol, int x, int y);
        MapObject(const MapObject& other) : QGraphicsRectItem(), static_object(other.static_object), dynamic_object(other.dynamic_object), x(other.x), y(other.y), color(other.color){}
        char static_object;
        std::vector<char> dynamic_object;
        int x;
        int y;
        QColor color;
        bool is_static();
        bool is_free();
};

#endif // MAP_OBJECT_H