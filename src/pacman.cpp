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

Pacman::Pacman(int x, int y, Map *map, QGraphicsView *view) : QObject(), map(map),view(view), direction(9){
    this->position = std::make_pair(x*50, y*50);
    this->setBrush(QBrush(QImage("./textures/pacman/pacman0.png")));
    this->setRect(0,0,50,50);
    this->setPen(Qt::NoPen);
    this->setPos(this->position.first, this->position.second);
    this->movement.push_back(this->position);

    mAnimation = new QVariantAnimation(this);
    mAnimation->setDuration(200);

    connect(mAnimation, &QVariantAnimation::valueChanged, this, &Pacman::onAnimationChanged);
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
    GameOverRect *game_over = new GameOverRect(map->map.size(),map->map[0].size(),200,100, this->view);
}

void Pacman::pacman_win(){
    QGraphicsScene *scene = new QGraphicsScene();
    QGraphicsTextItem *text = new QGraphicsTextItem("Congratulations!");
    QGraphicsTextItem *text2 = new QGraphicsTextItem("You have won!");
    text->setFont(QFont("Arial", 45));
    text2->setFont(QFont("Arial", 25));
    QRectF textRect = text->boundingRect();
    QPointF center(this->view->width() / 2.0 - textRect.width() / 2.0, this->view->height() / 2.0 - textRect.height() / 2.0);
    text->setPos(center + QPointF(5, 0));
    textRect = text2->boundingRect();
    QPointF center2(this->view->width() / 2.0 - textRect.width() / 2.0, this->view->height() / 2.0 - textRect.height() / 2.0);
    text2->setPos(center2 + QPointF(5, 55));

    // Add the image
    QPixmap image("./textures/misc/winner.png");
    QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(image);
    pixmapItem->setPos(this->view->width() / 2.0 - image.width() / 2.0 + 5, this->view->height() / 2.0 - image.height() / 2.0 + 165);

    scene->addItem(text);
    scene->addItem(text2);
    scene->addItem(pixmapItem);
    this->view->setScene(scene);
}
