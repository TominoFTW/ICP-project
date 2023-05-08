/**
 * @file backend.h
 * @authors Behal Tomas xbehal02, Kontrik Jakub xkontr02
 * @brief Declaration of backend class methods and variables.
 * @date 2023-05-08
 */
#ifndef BACKEND_H
#define BACKEND_H
#include <string>
#include <vector>
#include <utility>
#include <fstream>

#include "key.h"
#include "pacman.h"
#include "ghost.h"
#include "map.h"

/**
 * @class Backend
 * @brief A class that represents the backend of an application and inherits from QObject for singals.
 * This class is responsible for managing the application's logic and data.
*/
class Backend : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructor for the Backend class.
     * Initializes the pointer to the map to null.
    */
    Backend();
    ~Backend();

    /**
     * @brief Loads a map from a given file.
     * Deletes the existing map, if any, and creates a new map object from the given file.
     * @param filename The name of the file containing the map data.
     * @return A pointer to the loaded map object.
    */
    Map *load_map(std::string filename);

    /**
     * @brief Move the Pacman object in the specified direction.
     * If the movement is valid (i.e., the target cell is free), the Pacman is moved to the new position and the number of moves is incremented.
     * If the movement is not valid, the Pacman remains in its current position and the number of moves is not incremented.
     * @param pacman The Pacman object to move.
    */
    void pacman_move(Pacman &pacman);

    /**
     * @brief Moves a ghost in a random direction, avoiding collisions with walls and checking for collisions with Pacman.
     *
     * @param ghost The Ghost object to move.
     * @param pacman The Pacman object to check for collisions with.
     * @throw int If a collision with Pacman occurs.
    */
    void ghost_move(Ghost &ghost, Pacman &pacman);

    /**
     * @brief Checks for collisions between Pacman and a Ghost.
     *
     * @param pacman The Pacman object to check.
     * @param ghost The Ghost object to check.
     * @return True if a collision has occurred, false otherwise.
    */
    bool check_collision(Pacman &pacman, Ghost &ghost);

    /**
     * @brief Checks whether the game has been won, i.e. Pacman has reached the end and all keys have been collected.
     * @param end The coordinates of the end position.
     * @param pacman The coordinates of Pacman's current position.
     * @param size The number of remaining keys.
     * @throw int If the game has been won.
    */
    void check_win(std::pair<int, int> end, std::pair<int, int> pacman, int size);

    /**
     * @brief Handles key collection by Pacman, updating the key vector and emitting a signal to update the UI.
     * @param key The Key object to pick up.
     * @param pacman The Pacman object that picks up the key.
     * @param keys The vector of remaining keys.
    */
    void pick_key(Key &key, Pacman &pacman, std::vector<Key*> &keys);

    /**
     * @brief Returns the starting position of Pacman.
     * @return The starting position of Pacman as a pair of integers representing its row and column on the game board.
    */
    std::pair<int,int> get_pacman_start();

    /**
     * @brief Returns the starting positions of all ghosts.
     * @return A vector of pairs of integers representing the row and column indices of all ghosts' starting positions on the game board.
    */
    std::vector<std::pair<int,int>> get_ghosts_start();

    /**
     * @brief Returns the position of the portal on the game board.
     * @return The position of the portal as a pair of integers representing its row and column indices on the game board, multiplied by the size of each tile.
    */
    std::pair<int,int> get_portal_pos();

    /**
     * @brief Gets the positions of all the keys on the map.
     * @return A vector of pairs representing the positions of the keys.
    */
    std::vector<std::pair<int,int>> get_keys_pos();

    /**
     * @brief Reads the map layout from a replay file and saves it to a temporary file for replay purposes.
     * @param input_file The filename of the replay file.
    */
    void get_replay_map(std::string input_file);
    Map *map; ///< A pointer to the current map object.
    signals:
        /**
         * @brief Signal emitted when Pacman moves to a new position.
         * @param old_position The old position of Pacman.
        */
        void p_move(std::pair<int, int> old_position);

        /**
         * @brief Signal emitted when a ghost moves to a new position.
        */
        void g_move();

        /**
         * @brief Signal emitted when the number of moves made by Pacman is incremented.
         * @param moves The new number of moves made by Pacman.
        */
        void moves_increment(int moves);

        /**
         * @brief Signal emitted when the number of remaining keys is updated.
         * @param keys The new number of remaining keys.
        */
        void update_keys(int keys);

        /**
         * @brief Signal emitted when the game is won.
        */
        void win();
};




#endif // BACKEND_H
