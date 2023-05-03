#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QTimer>
#include "pacman.h"
#include "map.h"
#include "ghost.h"

class GameState: public QObject{
public:
    GameState(Pacman* pacman, QGraphicsScene *scene, Map &map);
    void add_ghost(Ghost &ghost);
    void set_pacman_dir(int direction);
private slots:
    void update();
private:
    Pacman *pacman;
    QGraphicsScene *scene;
    Map map;
    QTimer *timer;
    std::vector<Ghost*> ghosts;
};


#endif // GAMESTATE_H
