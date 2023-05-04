#ifndef SQUAREGRID_H
#define SQUAREGRID_H

#include <QWidget>
#include <QPainter>
#include <vector>
#include <utility>
#include "map_object.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include "map.h"

class SquareGrid : public QWidget
{

public:
    SquareGrid(Map *map, QGraphicsScene *scene, QWidget *parent = nullptr);
    std::pair<int, int> get_pacman();
    std::vector<std::pair<int, int>> get_ghosts();
    std::vector<std::pair<int, int>> get_keys();
    std::pair<int, int> get_end();


private:
    Map *map;
    std::pair<int, int> pacman;
    std::vector<std::pair<int, int>> ghosts;
    std::vector<std::pair<int, int>> keys;
    std::pair<int, int> end;
};

#endif // SQUAREGRID_H
