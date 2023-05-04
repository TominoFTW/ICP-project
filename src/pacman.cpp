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
#include "pacman.h"
#include "map.h"
#include <iostream>
#include <utility>
#include <QTimer>
#include <QObject>
#include "gameover_scene.h"
#include <QVariantAnimation>

Pacman::Pacman(int x, int y, Map *map, QGraphicsView *view) : QObject(), map(map),view(view), direction(10){
    this->position = std::make_pair(x*50, y*50);
    this->setBrush(QBrush(QImage("./textures/pacman/pacman0.png")));
    this->setRect(0,0,50,50);
    this->setPen(Qt::NoPen);
    this->setPos(this->position.first, this->position.second);
    this->movement.push_back(std::make_pair(this->position.first, this->position.second));

    mAnimation = new QVariantAnimation(this);
    mAnimation->setDuration(200);

    connect(mAnimation, &QVariantAnimation::valueChanged, this, &Pacman::onAnimationChanged);
}

void Pacman::move(int direction, QGraphicsScene &scene, Map &map){
    switch(this->direction){
        case 0:
            if (map.map[this->position.second/50][(this->position.first+50)/50]->is_free()){
                mAnimation->setStartValue(QRectF(this->position.first, this->position.second, 50, 50));
                this->position.first += 50;
                // this->setPos(this->position.first, this->position.second);
                mAnimation->setEndValue(QRectF(this->position.first, this->position.second, 50, 50));
                mAnimation->start();
            }
            this->movement.push_back(std::make_pair(this->position.first, this->position.second));
            this->setBrush(QBrush(QImage("./textures/pacman/pacman0.png")));

            break;
        case 1:
            if (map.map[(this->position.second+50)/50][this->position.first/50]->is_free()){
                mAnimation->setStartValue(QRectF(this->position.first, this->position.second, 50, 50));
                this->position.second += 50;
                // this->setPos(this->position.first, this->position.second);
                mAnimation->setEndValue(QRectF(this->position.first, this->position.second, 50, 50));
                mAnimation->start();
            }
            this->movement.push_back(std::make_pair(this->position.first, this->position.second));
            this->setBrush(QBrush(QImage("./textures/pacman/pacman1.png")));

            break;
        case 2:
            if (map.map[this->position.second/50][(this->position.first-50)/50]->is_free()){
                mAnimation->setStartValue(QRectF(this->position.first, this->position.second, 50, 50));
                this->position.first -= 50;
                // this->setPos(this->position.first, this->position.second);
                mAnimation->setEndValue(QRectF(this->position.first, this->position.second, 50, 50));
                mAnimation->start();
            }
            this->movement.push_back(std::make_pair(this->position.first, this->position.second));
            this->setBrush(QBrush(QImage("./textures/pacman/pacman2.png")));



            break;
        case 3:
            if (map.map[(this->position.second-50)/50][this->position.first/50]->is_free()){
                mAnimation->setStartValue(QRectF(this->position.first, this->position.second, 50, 50));
                this->position.second -= 50;
                // this->setPos(this->position.first, this->position.second);
                mAnimation->setEndValue(QRectF(this->position.first, this->position.second, 50, 50));
                mAnimation->start();
            }
            this->movement.push_back(std::make_pair(this->position.first, this->position.second));
            this->setBrush(QBrush(QImage("./textures/pacman/pacman3.png")));


            break;
        default:
            break;
    }
}
void Pacman::set_direction(int direction){
    this->direction = direction;
}
void Pacman::onAnimationChanged(const QVariant &value){
    this->setPos(value.toRectF().topLeft());
    update();
}

void Pacman::pacman_end(){

    // Calculate the position of the rectangle
    GameOverRect *game_over = new GameOverRect(map->map.size(),map->map[0].size(),200,100, this->view);
    throw std::runtime_error("Game Over");
}
