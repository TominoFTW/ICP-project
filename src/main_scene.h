#ifndef MAINSCENE_H
#define MAINSCENE_H
#include <QWidget>
#include <QPainter>
#include <QGraphicsScene>
#include "map.h"

class MainScene : public QGraphicsScene{
public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();
    Map *map;


};

#endif // MAINSCENE_H
