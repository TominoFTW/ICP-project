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

class Replay: public QObject{
public:
    Replay(QGraphicsScene *MainScene);
    void update_forward();
    void update_backward();
private:
    Pacman* pacman;
    Ghost* ghost;
    QGraphicsScene *scene;
    Map *map;
    QTimer *timer;
    int index = 0;
    std::vector<std::pair<int, int>> pacman_positions;
    std::vector<std::pair<int, int>> ghost_positions;
    void parseInput(std::ifstream &input);
};
#endif // REPLAY_H
