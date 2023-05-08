/**
 * @file gameover_scene.h
 * @authors Behal Tomas xbehal02, Kontrik Jakub xkontr02
 * @brief GameOverRect header.
 * @date 2023-05-08
*/

#ifndef GAMEOVERSCENE_H
#define GAMEOVERSCENE_H
#include <QtWidgets>
#include <QtWidgets>
#include <QGraphicsScene>
#include <QGraphicsBlurEffect>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QBrush>

/**
 * @class GameOverRect
 * @brief Class that represents the game over message.
*/
class GameOverRect : public QGraphicsRectItem{
    public:
    /**
     * @brief The GameOverRect class constructor creates a new game over message that is displayed
     * in a rectangular shape with the specified position and size. The message displays the text "Game Over",
     * instructions to press "R" to restart the game, and instructions to press "C" to save the replay.
     * @param x The x coordinate of the top-left corner of the rectangle.
     * @param y The y coordinate of the top-left corner of the rectangle.
     * @param width The width of the rectangle.
     * @param height The height of the rectangle.
     * @param view The graphics view where the game over message is displayed.
     * @param parent The parent item of the game over message.
    */
    GameOverRect(qreal x, qreal y, qreal width, qreal height, QGraphicsView *view,QGraphicsItem *parent = nullptr);

    private:
        QGraphicsView *view; ///< The graphics view where the game over message is displayed.
};

#endif // GAMEOVERSCENE_H
