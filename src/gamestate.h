/**
 * @file gamestate.h
 * @authors Behal Tomas xbehal02, Kontrik Jakub xkontri02
 * @brief Declaration of gamestate class methods and variables.
 * @date 2023-05-08
*/
#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QTimer>
#include "pacman.h"
#include "map.h"
#include "ghost.h"
#include "key.h"
#include "backend.h"
/**
 * @class GameState
 * @brief The GameState class represents the current state of the game.
 * The GameState class initializes the game with a QGraphicsView and a Backend object, which holds the game's logic.
 * It creates a Pacman object and several Ghost objects using the Backend object's information, as well as Key objects
 * at specific positions on the game board. It also sets up a timer to periodically update the game's state.
*/
class GameState: public QObject{
public:
    /**
     * @brief Constructor for the GameState class.
     * @param view The QGraphicsView on which the game will be displayed.
     * @param backend The Backend object holding the game's logic.
    */
    GameState(QGraphicsView *view, Backend *backend);
    ~GameState();

    /**
     * @brief Sets the direction of the Pacman object.
     * @param direction The direction to set.
    */
    void set_pacman_dir(int direction);

    /**
    * @brief Prints the game state to a replay file with a timestamp and updates the list of available replay files.
    * @details The function gets the current time and formats it as a timestamp to create a unique filename for the replay file.
    * It then writes the current state of the game to the replay file, including the map layout and the movements of the pacman and ghosts.
    * Finally, it updates the list of available replay files in the main window of the application.
    */
    void replay_print();

    /**
     * @brief Checks if the game has been stopped.
     * @return True if the game has been stopped, false otherwise.
    */
    bool stopped();
private slots:
    /**
     * @brief Updates the game state.
     * @details This function is called periodically by a QTimer object. It moves the pacman and ghosts and checks if the game has ended.
    */
    void update();
private:
    /**
     * @brief Adds a Ghost object to the game_state ghots vector.
     * @param ghost The Ghost object to add.
    */
    void add_ghost(Ghost &ghost);
    /**
     * @brief Adds a Key object to the game_state keys vector.
     * @param key The Key object to add.
    */
    void add_key(Key &key);
    Pacman *pacman; ///< The Pacman object.
    QGraphicsView *view; ///< The QGraphicsView object on which the game is displayed.
    Backend *backend; ///< The Backend object holding the game's logic.
    QTimer *timer; ///< The QTimer object that periodically updates the game's state.
    std::vector<Ghost*> ghosts; ///< A vector of Ghost objects.
    std::vector<Key*> keys; ///< A vector of Key objects.
    std::pair<int, int> end; ///< The coordinates of the end of the game.
    bool stop; ///< A flag that indicates whether the game has been stopped.
};


#endif // GAMESTATE_H
