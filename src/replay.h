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

class Replay: public QGraphicsScene{
public:
    Replay(QWidget *parent, MainScene *scene, std::string input_file, Backend *backend, QGraphicsView *view);
    void update_forward();
    void update_backward();
    void update_end();
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

};
#endif // REPLAY_H
