#ifndef PACMAN_H
#define PACMAN_H
#include "map_grid.h"
#include "map.h"
#include <utility>
#include <QTimer>
#include <QObject>
class Pacman: public QGraphicsRectItem {
    public:
        Pacman(int x, int y, Map &map,QGraphicsView *view);
        void move(int direction, QGraphicsScene &scene, Map &map);
        std::pair<int, int> position;
        void pacman_end();
        void set_direction(int direction);
    private:
        QGraphicsView *view;
        int direction;
        std::vector<std::pair<int, int>> movement;
        QTimer *timer;

};

#endif // PACMAN_H
