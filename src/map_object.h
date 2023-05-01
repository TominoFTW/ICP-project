#ifndef MAP_OBJECT_H
#define MAP_OBJECT_H
#include <vector>
#include <QColor>

class MapObject {
    public:
        MapObject(char symbol, int x, int y);
        char static_object;
        std::vector<char> dynamic_object;
        int x;
        int y;
        QColor mColor;
        bool is_static();
        bool is_free();
        QColor getColor();
};

#endif // MAP_OBJECT_H