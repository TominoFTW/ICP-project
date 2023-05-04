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
    GameOverRect(qreal x, qreal y, qreal width, qreal height, QGraphicsView *view,QGraphicsItem *parent = nullptr);

    private:
        QGraphicsView *view;
};

#endif // GAMEOVERSCENE_H
