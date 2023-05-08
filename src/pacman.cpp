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
#include <QGraphicsView>
#include <utility>

Pacman::Pacman(std::pair<int, int> map_index, Map *map, QGraphicsView *view) : QObject(), map(map),view(view), direction(9), moves(0){
    this->position = std::make_pair(map_index.first*50, map_index.second*50);
    this->setBrush(QBrush(QImage("./textures/pacman/pacman0.png")));
    this->setRect(0,0,50,50);
    this->setPen(Qt::NoPen);
    this->setPos(this->position.first, this->position.second);
    this->view->scene()->addItem(this);
    this->movement.push_back(this->position);

    mAnimation = new QVariantAnimation(this);
    mAnimation->setDuration(200);

    connect(mAnimation, &QVariantAnimation::valueChanged, this, &Pacman::onAnimationChanged);
}
Pacman::~Pacman(){
    delete mAnimation;
}
void Pacman::move(std::pair<int, int>old_position){
    mAnimation->setStartValue(QRectF(old_position.first, old_position.second, 50, 50));
    mAnimation->setEndValue(QRectF(this->position.first, this->position.second, 50, 50));
    mAnimation->start();
    this->setBrush(QBrush(QImage("./textures/pacman/pacman"+QString::number(this->direction)+".png")));
}
void Pacman::set_direction(int direction){
    this->direction = direction;
}
void Pacman::onAnimationChanged(const QVariant &value){
    this->setPos(value.toRectF().topLeft());
    update();
}

void Pacman::pacman_end(){
    GameOverRect *game_over = new GameOverRect(map->map.size(),map->map[0].size(),250,100, this->view);
}


int Pacman::get_direction(){
    return this->direction;
}
