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
class GameState: public QObject{
public:
    GameState(QGraphicsView *view, Map *map);
    ~GameState();
    void add_ghost(Ghost &ghost);
    void add_key(Key &key);
    void set_pacman_dir(int direction);
    std::pair<int, int> end;
private slots:
    void update();
private:
    Pacman *pacman;
    QGraphicsView *view;
    Map *map;
    QTimer *timer;
    std::vector<Ghost*> ghosts;
    std::vector<Key*> keys;
    bool stop;
    Backend backend;
};


#endif // GAMESTATE_H
