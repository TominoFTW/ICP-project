#ifndef SQUAREGRID_H
#define SQUAREGRID_H

#include <QWidget>
#include <QPainter>
#include <vector>
#include "map_object.h"

class SquareGrid : public QWidget
{

public:
    SquareGrid(const std::vector<std::vector<MapObject>>& data, QWidget *parent = nullptr);


private:
    std::vector<std::vector<MapObject>> mData;
};

#endif // SQUAREGRID_H