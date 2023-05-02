#ifndef SQUAREGRID_H
#define SQUAREGRID_H

#include <QWidget>
#include <QPainter>
#include <vector>
#include "map_object.h"
#include <QGraphicsScene>
#include <QGraphicsView>

class SquareGrid : public QWidget
{

public:
    SquareGrid(const std::vector<std::vector<MapObject>>& data, QGraphicsScene *scene, QWidget *parent = nullptr);


private:
    std::vector<std::vector<MapObject>> mData;
};

#endif // SQUAREGRID_H