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
    QStringList relativePaths;
    QStringList relativePaths2;

private:
    Ui::MainWindow *ui;
    MainScene* scene;
    QGraphicsScene* win_scene = nullptr;
    void win();
    QGraphicsView *view = nullptr;
    GameState *gamestate = nullptr;
    Replay *replay = nullptr;
    Backend *backend = nullptr;
    bool replay_flag = false;
    void showMapLevelsDialog();
    void showReplayDialog();
    void restartGame() {
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


};
#endif // MAINWINDOW_H
