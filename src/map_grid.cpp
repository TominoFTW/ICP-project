#include "map_grid.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QVBoxLayout>
#include <QGraphicsItem>
#include <iostream>
#include <tuple>
#include <utility>

SquareGrid::SquareGrid(const std::vector<std::vector<MapObject>>& data,QGraphicsScene* scene, QWidget *parent)
    : QWidget(parent)
    , mData(data)
{
    // QPixmap wall(":/textures/misc/wall.png");
    // QPixmap dot(":/textures/misc/dot.png");
    // QPixmap target(":/textures/misc/target.png");
    // QPixmap key(":/textures/misc/key.png");
    // QPixmap pacman(":/textures/pacman/pacman1.png");
    // QPixmap ghost(":/textures/ghost/ghost1.png");

    std::pair <int, int> pacman;
    std::vector<std::pair<int, int>> ghosts;

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
                mData[row][col].setBrush(QBrush(QImage("./textures/misc/dot.png").scaled(50,50)));
                this->ghosts.push_back(std::make_pair(col, row));
            }
            else{
                mData[row][col].setBrush(QBrush(QImage("./textures/misc/dot.png").scaled(50,50)));
                if (mData[row][col].color == Qt::darkYellow) {
                    this->pacman = std::make_pair(col, row);
                }
            }
            mData[row][col].setPen(Qt::NoPen);
            scene->addItem(&mData[row][col]);
        }
    }
}

std::pair<int, int> SquareGrid::get_pacman(){
    std::cout << "pacman" << std::endl;
    std::cout << std::get<0>(pacman) << ' ' << std::get<1>(pacman) << std::endl;
    return this->pacman;
}

std::vector<std::pair<int, int>> SquareGrid::get_ghosts(){
    for (int i = 0; i < ghosts.size(); i++) {
        std::cout << "ghost" << std::endl;
        std::cout << ghosts[i].first << ' ' << ghosts[i].second << std::endl;
    }
    return this->ghosts;
}
