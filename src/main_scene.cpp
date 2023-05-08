/**
 * @file main_scene.cpp
 * @authors Behal Tomas xbehal02, Kontrik Jakub xkontr02
 * @brief MainScene setup and implementation of methods.
 * @date 2023-05-08
*/

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QVBoxLayout>
#include <QGraphicsItem>
#include <iostream>
#include <utility>
#include <string>

#include "main_scene.h"
#include "map.h"

MainScene::MainScene(Backend *backend,QWidget *parent)
    : QGraphicsScene(parent)
{
    this->backend = backend;
    // looping through map and setting up all items
    for (int row = 0; row < (int)backend->map->map.size(); row++) {
        for (int col = 0; col < (int)backend->map->map[row].size(); col++) {
            backend->map->map[row][col]->setRect(col*50, row*50, 50, 50);
            if (backend->map->map[row][col]->color == Qt::black) {
                backend->map->map[row][col]->setBrush(QBrush(QImage("./textures/misc/wall.png").scaled(50,50)));
            }
            else if(backend->map->map[row][col]->color == Qt::blue) {
                backend->map->map[row][col]->setBrush(QBrush(QImage("./textures/misc/targer.png").scaled(50,50)));
            }
            else if (backend->map->map[row][col]->color == Qt::yellow) {
                backend->map->map[row][col]->setBrush(QBrush(QImage("./textures/misc/key.png").scaled(50,50)));
            }
            else if (backend->map->map[row][col]->color == Qt::blue) {
                backend->map->map[row][col]->setBrush(QBrush(QImage("./textures/misc/targer.png").scaled(50,50)));
            }
            else if (backend->map->map[row][col]->color == Qt::green) {
                backend->map->map[row][col]->setBrush(QBrush(QImage("./textures/misc/dot.png").scaled(50,50)));
            }
            else{
                backend->map->map[row][col]->setBrush(QBrush(QImage("./textures/misc/dot.png").scaled(50,50)));
            }
            backend->map->map[row][col]->setPen(Qt::NoPen);
            this->addItem(backend->map->map[row][col]);

        }
    }
    // create rectangles for moves and keys
    this->movesRect = new QGraphicsRectItem();
    this->movesRect->setRect(this->backend->map->width*50-30,0,120,30);
    this->movesRect->setBrush(Qt::gray);
    this->movesRect->setPen(Qt::NoPen);
    this->movesRect->setOpacity(0.90);

    this->movesText = new QGraphicsTextItem();
    this->movesText->setPlainText("Moves: 0");
    this->movesText->setDefaultTextColor(Qt::black);
    this->movesText->setFont(QFont("Arial", 14));
    QRectF rect = this->movesRect->rect();
    QPointF center = rect.center();
    QPointF text_pos = center - QPointF(movesText->boundingRect().width() / 2+5, movesText->boundingRect().height() / 2);
    movesText->setPos(text_pos);
    this->addItem(movesRect);
    this->addItem(movesText);

    this->keysRect = new QGraphicsRectItem();
    this->keysRect->setRect(10,0,120,30);
    this->keysRect->setBrush(Qt::gray);
    this->keysRect->setPen(Qt::NoPen);
    this->keysRect->setOpacity(0.90);

    this->keysText = new QGraphicsTextItem();
    this->keysText->setPlainText("Keys: 0");
    this->keysText->setDefaultTextColor(Qt::black);
    this->keysText->setFont(QFont("Arial", 14));
    rect = this->keysRect->rect();
    center = rect.center();
    text_pos = center - QPointF(keysText->boundingRect().width() / 2+5, keysText->boundingRect().height() / 2);
    keysText->setPos(text_pos);
    this->addItem(keysRect);
    this->addItem(keysText);
    
    // connect 
    connect(this->backend, &Backend::moves_increment, this, &MainScene::updateMovesText);
    connect(this->backend, &Backend::update_keys, this, &MainScene::updateKeysText);
}

void MainScene::updateMovesText(int moves){
    movesText->setPlainText("Moves: " + QString::number(moves));
}

void MainScene::updateKeysText(int keys){
    keysText->setPlainText("Keys: " + QString::number(keys));
}

MainScene::~MainScene(){
    // remove all items from scene so they can be reused after restart
    for (int row = 0; row < (int)backend->map->map.size(); row++) {
        for (int col = 0; col < (int)backend->map->map[row].size(); col++) {
            removeItem(backend->map->map[row][col]);
        }
    }
    delete movesText;
    delete movesRect;
}
