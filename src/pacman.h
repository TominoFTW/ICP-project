#ifndef PACMAN_H
#define PACMAN_H
#include "map_grid.h"
#include "map.h"
#include <utility>
#include <QTimer>
#include <QObject>
#include <QVariantAnimation>
//hello
class Pacman: public QObject, public QGraphicsRectItem {
    Q_OBJECT
    public:
        Pacman(int x, int y, Map &map,QGraphicsView *view);
        void move(int direction, QGraphicsScene &scene, Map &map);
        std::pair<int, int> position;
        void pacman_end();
        void set_direction(int direction);

    private slots:
        void onAnimationChanged(const QVariant &value);

    private:
        QGraphicsView *view;
        int direction;
        std::vector<std::pair<int, int>> movement;
        QTimer *timer;
        QVariantAnimation *mAnimation;

};

#endif // PACMAN_H
