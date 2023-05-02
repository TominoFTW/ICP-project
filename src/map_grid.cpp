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
    QPixmap wall(":/textures/misc/wall.png");
    QPixmap dot(":/textures/misc/dot.png");
    QPixmap target(":/textures/misc/target.png");
    QPixmap key(":/textures/misc/key.png");
    QPixmap pacman(":/textures/pacman/pacman1.png");
    QPixmap ghost(":/textures/ghost/ghost1.png");


    for (int row = 0; row < mData.size(); row++) {
        for (int col = 0; col < mData[row].size(); col++) {
            mData[row][col].setRect(col*50, row*50, 50, 50);
            if (mData[row][col].color == Qt::black) {
                // wall, so set texture of wall from ../textures/misc/wall.png
                mData[row][col].setBrush(QBrush(QImage("./textures/misc/wall.png").scaled(50,50)));
            }
            else if(mData[row][col].color == Qt::blue) {
                mData[row][col].setBrush(QBrush(QImage("./textures/misc/targer.png").scaled(50,50)));
            }
            else if (mData[row][col].color == Qt::yellow) {
                mData[row][col].setBrush(QBrush(QImage("./textures/misc/key.png").scaled(50,50)));
            }
            else if (mData[row][col].color == Qt::blue) {
                mData[row][col].setBrush(QBrush(QImage("./textures/misc/targer.png").scaled(50,50)));
            }
            else if (mData[row][col].color == Qt::green) {
                mData[row][col].setBrush(QBrush(QImage("./textures/ghosts/ghost1.png").scaled(50,50)));
            }
            else
                mData[row][col].setBrush(QBrush(QImage("./textures/misc/dot.png").scaled(50,50)));


            scene->addItem(&mData[row][col]);
        }
    }
}
