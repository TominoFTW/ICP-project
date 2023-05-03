#ifndef PACMAN_H
#define PACMAN_H
#include "map_grid.h"
#include "map.h"
#include <utility>
class Pacman: public QGraphicsRectItem {
    public:
        Pacman(int x, int y, Map &map);
        void move(int direction, QGraphicsScene &scene, Map &map);
    private:
        int direction;
        std::pair<int, int> position;
        std::vector<std::pair<int, int>> movement;

};

#endif // PACMAN_H
