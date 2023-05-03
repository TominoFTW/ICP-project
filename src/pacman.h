#ifndef PACMAN_H
#define PACMAN_H
#include "map_grid.h"
#include "map.h"
class Pacman: public QGraphicsRectItem {
    public:
        Pacman(int x, int y, Map &map);
        void move(int direction, QGraphicsScene &scene, Map &map);
    private:
        int direction;
        std::tuple<int, int> position;

};

#endif // PACMAN_H
