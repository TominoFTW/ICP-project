#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "map.h"
#include "map_object.h"
#include "map_grid.h"
#include <QLayout>
#include "pacman.h"
#include "ghost.h"
#include <utility>
#include "gamestate.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->map = new Map();
    //todo wrong free memory here
    this->scene = new QGraphicsScene(this);
    QGraphicsView* view = new QGraphicsView(this->scene, this);
    view->setFixedSize((int)map->map.size()*50+10, (int)map->map[0].size()*50+10);
    this->setFixedSize((map->width+2)*50+10, (map->height+2)*50+35);
    SquareGrid *grid = new SquareGrid(this->map,this->scene, this);
    grid->setFocusPolicy(Qt::StrongFocus);
    this->setCentralWidget(grid);
    this->setFocusPolicy(Qt::StrongFocus);
    auto pacman_cords = grid->get_pacman();
    this->pacman = new Pacman(pacman_cords.first, pacman_cords.second, map, view);
    scene->addItem(this->pacman);
    // todo toto musi ist preco
    auto ghosts_cords = grid->get_ghosts();
    auto key_cords = grid->get_keys();
    this->gamestate = new GameState(this->pacman, this->scene, this->map);
    this->gamestate->end.first = grid->get_end().first*50;
    this->gamestate->end.second = grid->get_end().second*50;
    for (int i = 0; i < (int)ghosts_cords.size(); i++) {
        Ghost *ghost = new Ghost(ghosts_cords[i].first, ghosts_cords[i].second, *map);
        this->gamestate->add_ghost(*ghost);
        scene->addItem(ghost);
    }
    for (int i = 0; i < (int)key_cords.size(); i++) {
        Key *key = new Key(key_cords[i].first, key_cords[i].second, this->map);
        this->gamestate->add_key(*key);
    }


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
        default:
            return;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
