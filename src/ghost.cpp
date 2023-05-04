#include <tuple>
#include "map_object.h"
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QBrush>
#include <QColor>
#include <QPen>
#include <QGraphicsItem>
#include "ghost.h"
#include "map.h"
#include <iostream>
#include <random>
#include <utility>
#include "pacman.h"
#include <QObject>
#include <QGraphicsView>

Ghost::Ghost(int x, int y, Map &map) : QObject(){
    this->direction = 0;
    this->position = std::make_pair(x*50, y*50);
    this->setBrush(QBrush(QImage("./textures/ghosts/ghost1.png").scaled(50,50)));
    this->setRect(0,0,50,50);
    this->setPen(Qt::NoPen);
    this->setPos(this->position.first, this->position.second);

    mAnimation = new QVariantAnimation(this);
    mAnimation->setDuration(200);

    connect(mAnimation, &QVariantAnimation::valueChanged, this, &Ghost::onAnimationChanged);
    
}

void Ghost::move(int id, QGraphicsScene &scene, Map &map, Pacman &pacman){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 3);
    check_collision(scene, map, pacman);
    bool moved = false;
    while (!moved){
        int direction = dis(gen);
        mAnimation->setStartValue(QRectF(this->position.first, this->position.second, 50, 50));
        switch(direction){
            case 0:
                if (map.map[this->position.second/50][(this->position.first+50)/50]->is_free()){
                    this->position.first += 50;
                    moved = true;
                }
                break;
            case 1:
                if (map.map[(this->position.second+50)/50][this->position.first/50]->is_free()){
                    this->position.second += 50;
                    moved = true;
                }
                break;
            case 2:
                if (map.map[this->position.second/50][(this->position.first-50)/50]->is_free()){
                    this->position.first -= 50;
                    moved = true;
                }
                break;
            case 3:
                if (map.map[(this->position.second-50)/50][this->position.first/50]->is_free()){
                    this->position.second -= 50;
                    moved = true;
                }
                break;
        }
        mAnimation->setEndValue(QRectF(this->position.first, this->position.second, 50, 50));
        mAnimation->start();
        // this->setPos(this->position.first, this->position.second);
    }
    check_collision(scene, map, pacman);
    std::cout << "Update" << std::endl;
    std::cout << std::get<0>(this->position)<< " " << std::get<1>(this->position) << std::endl;
}
void Ghost::onAnimationChanged(const QVariant &value){
    this->setPos(value.toRectF().topLeft());
    update();
}


void Ghost::check_collision(QGraphicsScene &scene, Map &map, Pacman &pacman){
    if (pacman.position == this->position){
        pacman.pacman_end();
    // todo
    }
}
