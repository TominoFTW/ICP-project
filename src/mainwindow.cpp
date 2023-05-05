#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "map.h"
#include "map_object.h"
#include <QLayout>
#include "pacman.h"
#include "ghost.h"
#include <utility>
#include "gamestate.h"
#include "main_scene.h"
#include "replay.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Pacmun");
    //todo wrong free memory here
    bool replay = false;
    this->scene = new MainScene(this);
    if (replay) {
        this->replay = new Replay(this, this->scene);
        // IDK je to sracka
    }
    this->view = new QGraphicsView(this->scene, this);
    view->setFixedSize((int)this->scene->map->map.size()*50+10, (int)this->scene->map->map[0].size()*50+10);
    this->setFixedSize((this->scene->map->width+2)*50+10, (this->scene->map->height+2)*50+35);
    this->setCentralWidget(view);
    view->setFocusPolicy(Qt::StrongFocus);
    this->setFocusPolicy(Qt::StrongFocus);
    view->setFocusPolicy(Qt::NoFocus);
    this->gamestate = new GameState(view, this->scene->map);
}


// registering users input with w-s-a-d and arrow keys
void MainWindow::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_W:
        case Qt::Key_Up:
            this->gamestate->set_pacman_dir(3);
            break;
        case Qt::Key_S:
        case Qt::Key_Down:
            this->gamestate->set_pacman_dir(1);
            break;
        case Qt::Key_A:
        case Qt::Key_Left:
            this->gamestate->set_pacman_dir(2);
            break;
        case Qt::Key_D:
        case Qt::Key_Right:
            this->gamestate->set_pacman_dir(0);
            break;
        case Qt::Key_R:
            this->restartGame();
            break;
        default:
            return;
    }
}
MainWindow::~MainWindow()
{
    delete ui;
    delete this->gamestate;
    delete this->scene;
}
