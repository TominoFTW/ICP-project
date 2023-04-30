#ifndef MAP_OBJECT_H
#define MAP_OBJECT_H
#include <vector>

class MapObject {
    public:
        MapObject(char symbol, int x, int y);
        char static_object;
        std::vector<char> dynamic_object;
        int x;
        int y;
        bool is_static();
        bool is_free();
};

#endif // MAP_OBJECT_H