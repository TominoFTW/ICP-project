/**
 * @file key.h
 * @authors Behal Tomas xbehal02, Kontrik Jakub xkontr02
 * @brief Key header.
 * @date 2023-05-08
*/
#ifndef KEY_H
#define KEY_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QKeyEvent>
#include <QGraphicsScene>

#include "map.h"
/**
 * @class Key
 * @brief Class that represents the key that the player has to pick up in order to win the game.
*/
class Key: public QGraphicsRectItem{
    public:
        /**
         * @brief The constructor of the Key class.
         * @param position The map position of the key.
         * @param map A pointer to the Map object that the key belongs to.
        */
        Key(std::pair<int, int> position, Map *map);

        /**
         * @brief Updates the key on the map based on whether it has been picked or not.
        */
        void update();

        std::pair<int, int> position; ///< The position of the key.
        bool picked; ///< Whether the key has been picked up or not.

    private:
        Map *map; ///< A pointer to the Map object that the key belongs to.
};

#endif // KEY_H
