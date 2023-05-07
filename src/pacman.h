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
        Pacman(std::pair<int,int> map_index, Map *map, QGraphicsView *view);
        ~Pacman();
        std::pair<int, int> position;
        int moves;
        void pacman_end();
        std::vector<std::pair<int,int>> movement;
        void set_direction(int direction);
        int get_direction();
    private slots:
        void onAnimationChanged(const QVariant &value);

    private:
        Map *map;
        QGraphicsView *view;
        int direction;
        QVariantAnimation *mAnimation;

    public slots:
        void move(std::pair<int, int> old_position);

};

#endif // PACMAN_H
