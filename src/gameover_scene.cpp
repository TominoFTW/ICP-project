/**
 * @file gameover_scene.cpp
 * @authors Behal Tomas xbehal02, Kontrik Jakub xkontr02
 * @brief Declaration of Gameover retangle after colision.
 * @date 2023-05-08
 */
#include "gameover_scene.h"

GameOverRect::GameOverRect(qreal x, qreal y, qreal width, qreal height, QGraphicsView *view, QGraphicsItem *parent)
        : QGraphicsRectItem((x*50+10)/2-width/2,(y*50+10)/2-height/2, width, height, parent), view(view)
{
    setBrush(Qt::gray);
    setPen(Qt::NoPen);
    setOpacity(0.95);

    QGraphicsTextItem *text = new QGraphicsTextItem("Game Over", this);
    text->setDefaultTextColor(Qt::black);
    text->setFont(QFont("Arial", 20));
    QRectF rect = this->rect();
    QPointF center = rect.center();
    QPointF text_pos = center - QPointF(text->boundingRect().width() / 2, text->boundingRect().height() / 2+20);
    text->setPos(text_pos);

    QGraphicsTextItem *text2 = new QGraphicsTextItem("Press \"R\" to restart", this);
    text2->setDefaultTextColor(Qt::white);
    text2->setFont(QFont("Arial", 14));
    // Position the "Press R to restart" text below the "Game Over" text
    QPointF text2_pos = center - QPointF(text2->boundingRect().width() / 2, -rect.height() / 100+5);
    text2->setPos(text2_pos);
    QGraphicsTextItem *text3 = new QGraphicsTextItem("Press \"C\" to save the replay", this);
    text3->setDefaultTextColor(Qt::white);
    text3->setFont(QFont("Arial", 11));
    // Position the "Press C to save the replay" text below the "Game Over" text
    QPointF text3_pos = center - QPointF(text3->boundingRect().width() / 2, -rect.height() / 4.5);
    text3->setPos(text3_pos);

    this->view->scene()->addItem(this);
}
