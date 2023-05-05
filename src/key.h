#ifndef KEY_H
#define KEY_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QKeyEvent>
#include <QGraphicsScene>
#include "map.h"

class Key: public QGraphicsRectItem{
    public:
        Key(std::pair<int, int> position, Map *map);
        void update();
        std::pair<int, int> position;
        bool picked;

    private:
        Map *map;
};

#endif // KEY_H