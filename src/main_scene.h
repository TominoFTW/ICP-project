#ifndef MAINSCENE_H
#define MAINSCENE_H
#include <QWidget>
#include <QPainter>
#include <QGraphicsScene>
#include "map.h"

class MainScene : public QGraphicsScene{
public:
    MainScene(QWidget *parent = nullptr);
    std::pair<int, int> get_pacman();
    std::vector<std::pair<int, int>> get_ghosts();
    std::vector<std::pair<int, int>> get_keys();
    std::pair<int, int> get_end();
    Map *map;


private:
    std::pair<int, int> pacman;
    std::vector<std::pair<int, int>> ghosts;
    std::vector<std::pair<int, int>> keys;
    std::pair<int, int> end;
};

#endif // MAINSCENE_H
