#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <iostream>
#include "map.h"
#include <vector>
#include "pacman.h"
#include "ghost.h"
#include "gamestate.h"
#include "main_scene.h"
#include "replay.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *) override;

private:
    Ui::MainWindow *ui;
    // todo runtime class with global variables
    Pacman *pacman;
    MainScene* scene;
    QGraphicsView *view;
    GameState *gamestate;
    Replay *replay;
    void restartGame() {
        delete this->gamestate;
        delete this->scene;
        this->scene = new MainScene(this);
        this->view->setScene(this->scene);
        this->gamestate = new GameState(this->view, this->scene->map);
}


};
#endif // MAINWINDOW_H
