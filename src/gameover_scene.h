#ifndef GAMEOVERSCENE_H
#define GAMEOVERSCENE_H
#include <QtWidgets>

#include <QtWidgets>
#include <QGraphicsScene>
#include <QGraphicsBlurEffect>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QBrush>



#include <QtWidgets>

class GameOverRect : public QGraphicsRectItem{
    public:
    GameOverRect(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = nullptr);
};

#endif // GAMEOVERSCENE_H
