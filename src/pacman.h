/**
 * @file pacman.h
 * @authors Behal Tomas xbehal02, Kontrik Jakub xkontr02
 * @brief Declaration of pacman class.
 * @date 2023-05-08
*/
#ifndef PACMAN_H
#define PACMAN_H
#include "map.h"
#include <utility>
#include <QTimer>
#include <QObject>
#include <QVariantAnimation>
#include <QGraphicsView>
#include <utility>
#include "gameover_scene.h"
/**
 * @brief The Pacman class is responsible for the pacman object and its movement.
 */
class Pacman: public QObject, public QGraphicsRectItem {
    Q_OBJECT
    public:
        /**
         * @brief Construct a new Pacman object.
         * @param map_index Coordinates of the pacman on the map.
         * @param map Map object that contains the map layout.
         * @param view The QGraphicsView object that the game is displayed on.
         */
        Pacman(std::pair<int,int> map_index, Map *map, QGraphicsView *view);
        ~Pacman();

        /**
         * @brief Creates game over scene and displays it.
         */
        void pacman_end();

        /**
         * @brief Sets the direction of the pacman.
         * @param direction The direction that the pacman will be set to.
         */
        void set_direction(int direction);

        /**
         * @brief Gets the direction of the pacman.
         * 
         * @return The direction of the pacman.
         */
        int get_direction();

        int moves;
        std::pair<int, int> position;
        std::vector<std::pair<int,int>> movement;
        
    public slots:
        void move(std::pair<int, int> old_position);
    private slots:
        void onAnimationChanged(const QVariant &value);

    private:
        Map *map;
        QGraphicsView *view;
        int direction;
        QVariantAnimation *mAnimation;
        GameOverRect *game_over = nullptr;


};

#endif // PACMAN_H
