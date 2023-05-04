#include "gameover_scene.h"

GameOverRect::GameOverRect(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent)
        : QGraphicsRectItem(x, y, width, height, parent)
    {
        setBrush(Qt::transparent);
    }