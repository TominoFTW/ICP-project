#ifndef GHOST_H
#define GHOST_H
#include "map_grid.h"
#include "map.h"
class Ghost: public QGraphicsRectItem {
    public:
        Ghost(int x, int y, Map &map);
        void move(int id, QGraphicsScene &scene, Map &map);
    private:
        int direction;
        std::tuple<int, int> position;

};

#endif // GHOST_H