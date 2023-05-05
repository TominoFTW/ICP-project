#ifndef PACMAN_H
#define PACMAN_H
#include "map.h"
#include <utility>
#include <QTimer>
#include <QObject>
#include <QVariantAnimation>
#include <QGraphicsView>
#include <utility>
//hello
class Pacman: public QObject, public QGraphicsRectItem {
    Q_OBJECT
    public:
        Pacman(std::pair<int,int> map_index, Map *map,QGraphicsView *view);
        void move(std::pair<int, int> old_position);
        std::pair<int, int> position;
        void pacman_end();
        void pacman_win();
        int direction;
        std::vector<std::pair<int,int>> movement;
        void set_direction(int direction);

    private slots:
        void onAnimationChanged(const QVariant &value);

    private:
        Map *map;
        QGraphicsView *view;
        QVariantAnimation *mAnimation;

};

#endif // PACMAN_H
