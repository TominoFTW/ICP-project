/**
 * @file main_scene.h
 * @authors Behal Tomas xbehal02, Kontrik Jakub xkontr02
 * @brief MainScene header.
 * @date 2023-05-08
*/
#ifndef MAINSCENE_H
#define MAINSCENE_H
#include <QWidget>
#include <QPainter>
#include <QGraphicsScene>
#include "map.h"
#include "backend.h"
/**
 * @class MainScene
 * @brief Class that represents the main scene of the game.
*/
class MainScene : public QGraphicsScene{
public:
    /**
     * @brief Constructs a MainScene object with a backend and a parent widget.
     * @param backend A pointer to the Backend object which stores the map data.
     * @param parent A pointer to the parent widget of this MainScene object.
    */
    MainScene(Backend *backend, QWidget *parent = nullptr);
    ~MainScene();

    QGraphicsTextItem *movesText; ///< The QGraphicsTextItem object that displays the number of moves.
    QGraphicsRectItem *movesRect; ///< The QGraphicsRectItem object that displays the number of moves.
    QGraphicsTextItem *keysText; ///< The QGraphicsTextItem object that displays the number of keys.
    QGraphicsRectItem *keysRect; ///< The QGraphicsRectItem object that displays the number of keys.
    Backend *backend; ///< A pointer to the Backend object which stores the map data.
    public slots:
        /**
         * @brief Updates the number of moves displayed on the screen.
         * @param moves The number of moves to be displayed.
        */
        void updateMovesText(int moves);
        /**
         * @brief Updates the number of keys displayed on the screen.
         * @param keys The number of keys to be displayed.
        */
        void updateKeysText(int keys);
};

#endif // MAINSCENE_H
