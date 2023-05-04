#ifndef GHOST_H
#define GHOST_H
#include "map_grid.h"
#include "map.h"
#include <utility>
#include "pacman.h"
#include <QObject>
class Ghost: public QObject, public QGraphicsRectItem {
    Q_OBJECT
    public:
        Ghost(int x, int y, Map &map);
        void move(int id, QGraphicsScene &scene, Map &map, Pacman &pacman);
        void check_collision(QGraphicsScene &scene, Map &map, Pacman &pacman);
    private slots:
        void onAnimationChanged(const QVariant &value);
    private:
        int direction;
        std::pair<int, int> position;

        QVariantAnimation *mAnimation;

};

#endif // GHOST_H
