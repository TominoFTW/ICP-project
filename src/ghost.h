#ifndef GHOST_H
#define GHOST_H
#include "map.h"
#include <utility>
#include "pacman.h"
#include <QObject>
#include <QGraphicsView>
class Ghost: public QObject, public QGraphicsRectItem {
    Q_OBJECT
    public:
        Ghost(std::pair<int,int> map_index, QGraphicsView *view);
        void move(std::pair<int, int> old_position);
        void check_collision(QGraphicsScene &scene, Map &map, Pacman &pacman);
        int direction;
        std::pair<int, int> position;
        std::vector<std::pair<int, int>> movement;
    private slots:
        void onAnimationChanged(const QVariant &value);
    private:
        QGraphicsView *view;
        QVariantAnimation *mAnimation;

};

#endif // GHOST_H
