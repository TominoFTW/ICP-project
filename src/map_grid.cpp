#include "map_grid.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QVBoxLayout>
#include <QGraphicsItem>
#include <iostream>

SquareGrid::SquareGrid(const std::vector<std::vector<MapObject>>& data, QWidget *parent)
    : QWidget(parent)
    , mData(data)
{
    QGraphicsScene* scene = new QGraphicsScene(this);
    QGraphicsView* view = new QGraphicsView(scene, this);
    view->setFixedSize(800, 600);

    // Generate square items and add them to the scene
    for (int row = 0; row < mData.size(); row++) {
        for (int col = 0; col < mData[row].size(); col++) {
            mData[row][col].setRect(col*50, row*50, 50, 50);
            mData[row][col].setBrush(mData[row][col].color);
            scene->addItem(&mData[row][col]);
        }
    }
}


