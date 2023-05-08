/**
 * @file replay.h
 * @authors Behal Tomas xbehal02, Kontrik Jakub xkontr02
 * @brief Replay header.
 * @date 2023-05-08
 */
#ifndef REPLAY_H
#define REPLAY_H
#include "replay.h"
#include "map.h"
#include "map_object.h"
#include <cstring>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include "pacman.h"
#include "ghost.h"
#include <iostream>
#include <QTimer>
#include <QObject>
#include <utility>
#include "backend.h"
#include "main_scene.h"

/**
 * @brief The Replay class is responsible for replaying a game based on the input file and displaying it on the QGraphicsView.
 */
class Replay: public QGraphicsScene{
    public:
        /**
         * @brief Constructor of the Replay class, it parses the input file and creates the game objects.
         * @param parent The parent widget that the replay will be displayed on.
         * @param scene The MainScene object that contains the layout and the game objects.
         * @param input_file The path to the input file containing the game data.
         * @param backend The Backend object that manages the game mechanics.
         * @param view The QGraphicsView object that the game is displayed on.
         */
        Replay(QWidget *parent, MainScene *scene, std::string input_file, Backend *backend, QGraphicsView *view);
        ~Replay();

        /**
         * @brief update_forward updates the game state by moving the game objects forward by one step.
         */
        void update_forward();

        /**
         * @brief update_backward updates the game state by moving the game objects backward by one step.
         */
        void update_backward();
        
        /**
         * @brief update_end updates the game state by moving the game objects to the end of the game.
         */
        void update_end();

        /**
         * @brief update_start updates the game state by moving the game objects to the start of the game.
         */
        void update_start();
        
        std::string input_map;
    private:
        Pacman* pacman;
        std::vector<Ghost*> ghosts;
        std::vector<Key*> keys;
        std::vector<Key*> picked_keys;
        MainScene *scene;
        QGraphicsView *view;
        Backend *backend;
        Map *map;
        QTimer *timer;
        std::pair<int, int> end;
        int index = 0;
        std::vector<std::pair<int, int>> pacman_positions;
        std::vector<std::vector<std::pair<int, int>>> ghost_positions;
        void parseInput(std::ifstream &input);
        void add_ghost(Ghost &ghost);
        void add_key(Key &key);
        int pacman_possible_moves();
        int pacman_num_moves;
};
#endif // REPLAY_H
