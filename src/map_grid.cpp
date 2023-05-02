#include "map_grid.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QVBoxLayout>
#include <QGraphicsItem>
#include <iostream>

SquareGrid::SquareGrid(const std::vector<std::vector<MapObject>>& data,QGraphicsScene* scene, QWidget *parent)
    : QWidget(parent)
    , mData(data)
{

    for (int row = 0; row < mData.size(); row++) {
        for (int col = 0; col < mData[row].size(); col++) {
            mData[row][col].setRect(col*50, row*50, 50, 50);
            mData[row][col].setBrush(mData[row][col].color);
            scene->addItem(&mData[row][col]);
        }
    }
}
