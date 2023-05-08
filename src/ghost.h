/**
 * @file ghost.h
 * @authors Behal Tomas xbehal02, Kontrik Jakub xkontr02
 * @brief Ghost header.
 * @date 2023-05-08
*/

#ifndef GHOST_H
#define GHOST_H
#include <utility>
#include <QObject>
#include <QGraphicsView>

#include "pacman.h"
#include "map.h"
/**
 * @class Ghost
 * @brief Class that represents the ghosts in the game.
*/
class Ghost: public QObject, public QGraphicsRectItem {
    Q_OBJECT
    public:
        /**
         * @brief Construct a new Ghost object.
         * @param map_index The initial index of the Ghost in the Map.
         * @param view The QGraphicsView object that the Ghost will be added to.
         */
        Ghost(std::pair<int,int> map_index, QGraphicsView *view);
        ~Ghost();

        /**
         * @brief Moves the Ghost on window to its new position using a QVariantAnimation object.
        */
        void move();

        std::pair<int, int> position; ///< The current position of the Ghost.
        std::pair<int, int> old_position = position; ///< The previous position of the Ghost.
        std::vector<std::pair<int, int>> movement; ///< The history of the Ghost's movement.
    private slots:
        /**
         * @brief Slot that is called when the animation changes.
        */
        void onAnimationChanged(const QVariant &value);
    private:
        QGraphicsView *view; ///< The QGraphicsView object that the Ghost is added to.
        QVariantAnimation *mAnimation; ///< The QVariantAnimation object that is used to animate the Ghost.
        int direction; ///< The direction that the Ghost is moving in.

};

#endif // GHOST_H
