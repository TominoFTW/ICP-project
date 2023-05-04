#include "main_scene.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QVBoxLayout>
#include <QGraphicsItem>
#include <iostream>
#include <tuple>
#include <utility>
#include "map.h"


MainScene::MainScene(QWidget *parent)
    : QGraphicsScene(parent)
{
    // QPixmap wall(":/textures/misc/wall.png");
    // QPixmap dot(":/textures/misc/dot.png");
    // QPixmap target(":/textures/misc/target.png");
    // QPixmap key(":/textures/misc/key.png");
    // QPixmap pacman(":/textures/pacman/pacman1.png");
    // QPixmap ghost(":/textures/ghost/ghost1.png");
    this->map= new Map("./examples/map-01.txt");

    for (int row = 0; row < map->map.size(); row++) {
        for (int col = 0; col < map->map[row].size(); col++) {
            map->map[row][col]->setRect(col*50, row*50, 50, 50);
            if (map->map[row][col]->color == Qt::black) {
                // wall, so set texture of wall from ../textures/misc/wall.png
                map->map[row][col]->setBrush(QBrush(QImage("./textures/misc/wall.png").scaled(50,50)));
            }
            else if(map->map[row][col]->color == Qt::blue) {
                map->map[row][col]->setBrush(QBrush(QImage("./textures/misc/targer.png").scaled(50,50)));
                this->end = std::make_pair(col, row);
            }
            else if (map->map[row][col]->color == Qt::yellow) {
                map->map[row][col]->setBrush(QBrush(QImage("./textures/misc/key.png").scaled(50,50)));
                this->keys.push_back(std::make_pair(col, row));
            }
            else if (map->map[row][col]->color == Qt::blue) {
                map->map[row][col]->setBrush(QBrush(QImage("./textures/misc/targer.png").scaled(50,50)));
            }
            else if (map->map[row][col]->color == Qt::green) {
                map->map[row][col]->setBrush(QBrush(QImage("./textures/misc/dot.png").scaled(50,50)));
                this->ghosts.push_back(std::make_pair(col, row));
            }
            else{
                map->map[row][col]->setBrush(QBrush(QImage("./textures/misc/dot.png").scaled(50,50)));
                if (map->map[row][col]->color == Qt::darkYellow) {
                    this->pacman = std::make_pair(col, row);
                }
            }
            map->map[row][col]->setPen(Qt::NoPen);
            this->addItem(map->map[row][col]);

        }
    }
}

std::pair<int, int> MainScene::get_pacman(){
    std::cout << "pacman" << std::endl;
    std::cout << std::get<0>(pacman) << ' ' << std::get<1>(pacman) << std::endl;
    return this->pacman;
}

std::pair<int, int> MainScene::get_end(){
    return this->end;
}

std::vector<std::pair<int, int>> MainScene::get_ghosts(){
    return this->ghosts;
}
std::vector<std::pair<int, int>> MainScene::get_keys(){
    return this->keys;
}
