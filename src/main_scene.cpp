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
#include <string>

MainScene::MainScene(Backend *backend,QWidget *parent)
    : QGraphicsScene(parent)
{
    // QPixmap wall(":/textures/misc/wall.png");
    // QPixmap dot(":/textures/misc/dot.png");
    // QPixmap target(":/textures/misc/target.png");
    // QPixmap key(":/textures/misc/key.png");
    // QPixmap pacman(":/textures/pacman/pacman1.png");
    // QPixmap ghost(":/textures/ghost/ghost1.png");

    // if (true){
    //     this->map= new Map("./examples/tmp.txt");
    // }
    // else{
    //     this->map= new Map("./examples/map-01.txt");
    // }
    this->backend = backend;

    for (int row = 0; row < backend->map->map.size(); row++) {
        for (int col = 0; col < backend->map->map[row].size(); col++) {
            backend->map->map[row][col]->setRect(col*50, row*50, 50, 50);
            if (backend->map->map[row][col]->color == Qt::black) {
                // wall, so set texture of wall from ../textures/misc/wall.png
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
    this->movesRect = new QGraphicsRectItem();
    this->movesRect->setRect(this->backend->map->width*50-15,0,100,30);
    this->movesRect->setBrush(Qt::gray);
    this->movesRect->setPen(Qt::NoPen);
    this->movesRect->setOpacity(0.90);

    this->movesText = new QGraphicsTextItem();
    this->movesText->setPlainText("Moves: 0");
    this->movesText->setDefaultTextColor(Qt::black);
    this->movesText->setFont(QFont("Arial", 14));
    QRectF rect = this->movesRect->rect();
    QPointF center = rect.center();
    QPointF text_pos = center - QPointF(movesText->boundingRect().width() / 2, movesText->boundingRect().height() / 2);
    movesText->setPos(text_pos);
    this->addItem(movesRect);
    this->addItem(movesText);
    // connect 
    connect(this->backend, &Backend::moves_increment, this, &MainScene::updateMovesText);
}
void MainScene::updateMovesText(int moves)
{
    movesText->setPlainText("Moves: " + QString::number(moves));
}
MainScene::~MainScene(){
    for (int row = 0; row < backend->map->map.size(); row++) {
        for (int col = 0; col < backend->map->map[row].size(); col++) {
            removeItem(backend->map->map[row][col]);
        }
    }
    delete movesText;
    delete movesRect;
}

