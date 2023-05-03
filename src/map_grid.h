#ifndef SQUAREGRID_H
#define SQUAREGRID_H

#include <QWidget>
#include <QPainter>
#include <vector>
#include <utility>
#include "map_object.h"
#include <QGraphicsScene>
#include <QGraphicsView>

class SquareGrid : public QWidget
{

public:
    SquareGrid(const std::vector<std::vector<MapObject>>& data, QGraphicsScene *scene, QWidget *parent = nullptr);
    std::pair<int, int> get_pacman();
    std::vector<std::pair<int, int>> get_ghosts();

private:
    std::vector<std::vector<MapObject>> mData;
    std::pair<int, int> pacman;
    std::vector<std::pair<int, int>> ghosts;
};

#endif // SQUAREGRID_H
