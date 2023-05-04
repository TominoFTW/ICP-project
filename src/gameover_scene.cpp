#include "gameover_scene.h"

GameOverRect::GameOverRect(qreal x, qreal y, qreal width, qreal height, QGraphicsView *view, QGraphicsItem *parent)
        : QGraphicsRectItem((x*50+10)/2-width/2,(y*50+10)/2-height/2, width, height, parent), view(view)
    {

        setBrush(Qt::gray);
        setPen(Qt::NoPen);
        setOpacity(0.9);

        QGraphicsTextItem *text = new QGraphicsTextItem("Game Over", this);
        text->setDefaultTextColor(Qt::black);
        text->setFont(QFont("Arial", 20));
        QRectF rect = this->rect();
        QPointF center = rect.center();
        QPointF text_pos = center - QPointF(text->boundingRect().width() / 2, text->boundingRect().height() / 2);
        text->setPos(text_pos);

        QGraphicsTextItem *text2 = new QGraphicsTextItem("Press \"R\" to restart", this);
        text2->setDefaultTextColor(Qt::white);
        text2->setFont(QFont("Arial", 14));
        // Position the "Press R to restart" text below the "Game Over" text
        QPointF text2_pos = center - QPointF(text2->boundingRect().width() / 2, -rect.height() / 8);
        text2->setPos(text2_pos);

        this->view->scene()->addItem(this);
    }
