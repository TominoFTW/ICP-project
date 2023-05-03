#ifndef GHOST_H
#define GHOST_H
#include "map_grid.h"
#include "map.h"
#include <utility>
#include "pacman.h"
class Ghost: public QGraphicsRectItem {
    public:
        Ghost(int x, int y, Map &map);
        void move(int id, QGraphicsScene &scene, Map &map, Pacman &pacman);
        void check_collision(QGraphicsScene &scene, Map &map, Pacman &pacman);
    private:
        int direction;
        std::pair<int, int> position;

};

#endif // GHOST_H
