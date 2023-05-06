#ifndef MAINSCENE_H
#define MAINSCENE_H
#include <QWidget>
#include <QPainter>
#include <QGraphicsScene>
#include "map.h"

class MainScene : public QGraphicsScene{
public:
    MainScene(Map *map, QWidget *parent = nullptr);
    ~MainScene();
    Map *map;
    QGraphicsTextItem *movesText;
    public slots:
        void updateMovesText();
};

#endif // MAINSCENE_H
