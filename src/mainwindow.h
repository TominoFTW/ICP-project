/**
 * @file mainwindow.h
 * @authors Behal Tomas xbehal02, Kontrik Jakub xkontr02
 * @brief MainWindow header.
 * @date 2023-05-08
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <iostream>
#include <vector>

#include "gamestate.h"
#include "main_scene.h"
#include "replay.h"

// Created by Qt Designer
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief The MainWindow class represents the main window of the Pacman game.
 * This class initializes the user interface, sets up the backend, and connects the UI with the backend. It also sets up the menu bar and actions for the user to interact with the game.
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the MainWindow class.
     * @param parent The parent widget of the main window.
    */
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *) override;

    QStringList relativePaths; ///< A list of relative paths to the map files.
    QStringList relativePaths2; ///< A list of relative paths to the replay files.

private:
    Ui::MainWindow *ui; ///< The user interface of the main window. Created by Qt Designer.
    MainScene* scene = nullptr; ///< The main scene of the game.
    QGraphicsScene* win_scene = nullptr; ///< The scene that displays the winning message.
    QGraphicsView *view = nullptr; ///< The QGraphicsView object that the game is displayed on.
    GameState *gamestate = nullptr; ///< The GameState object that holds the current state of the game.
    Replay *replay = nullptr; ///< The Replay object that holds the current state of the replay.
    Backend *backend = nullptr; ///< The Backend object that holds the game's logic.
    bool replay_flag = false; ///< A flag that indicates whether the game is being played or replayed. 
    bool exception_flag = false; ///< A flag that indicates whether an exception has been thrown.
    /**
     * @brief Creates a new QGraphicsScene to display the winning message.
     * This function creates a new QGraphicsScene and adds several QGraphicsItems to it to display the winning message.
     */
    void win();

    /**
     * @brief Opens a dialog to show available map levels and loads the selected map when a level button is clicked.
    */
    void showMapLevelsDialog();

    /**
     * @brief Opens a dialog to show available replays and loads the selected replay when a level button is clicked.
    */
    void showReplayDialog();

    /**
     * @brief Resets the game to its initial state.
     * Map is preserved, but the player's moves and keys are reset.
     * Creates a new Replay object and loads the replay file into it.
     * Modifies the UI to display buttons for the replay.
    */
    void restartGame() {
        this->blockSignals(false);
        if (this->gamestate != nullptr){
            delete this->gamestate;
            this->gamestate = nullptr;
        }
        if (this->scene != nullptr){
            delete this->scene;
            this->scene = nullptr;
        }
        if (this->win_scene != nullptr){
            delete this->win_scene;
            this->win_scene = nullptr;
        }
        this->scene = new MainScene(this->backend,this);

        this->view->setScene(this->scene);
        this->gamestate = new GameState(this->view, backend);
    }
    signals:
        /**
         * @brief Signal that is emitted if game is stopped and user wants to save replay.
        */
        void save_replay();


};
#endif // MAINWINDOW_H
