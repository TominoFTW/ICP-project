#ifndef MAINSCENE_H
#define MAINSCENE_H
#include <QWidget>
#include <QPainter>
#include <QGraphicsScene>
#include "map.h"
#include "backend.h"

class MainScene : public QGraphicsScene{
public:
    MainScene(Backend *backend, QWidget *parent = nullptr);
    ~MainScene();
    QGraphicsTextItem *movesText;
    QGraphicsRectItem *movesRect;
    Backend *backend;
    public slots:
        void updateMovesText();
};

#endif // MAINSCENE_H
