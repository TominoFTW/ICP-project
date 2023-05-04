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
        Ghost(int x, int y, Map &map);
        void move(std::pair<int, int> old_position);
        void check_collision(QGraphicsScene &scene, Map &map, Pacman &pacman);
        int direction;
        std::pair<int, int> position;
    private slots:
        void onAnimationChanged(const QVariant &value);
    private:

        QVariantAnimation *mAnimation;

};

#endif // GHOST_H
