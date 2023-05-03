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
    this->map = Map();
    //todo wrong free memory here
    this->scene = new QGraphicsScene(this);
    QGraphicsView* view = new QGraphicsView(this->scene, this);
    view->setFixedSize((int)map.map.size()*50+10, (int)map.map[0].size()*50+10);
    this->setFixedSize((map.width+2)*50+10, (map.height+2)*50+35);
    SquareGrid *grid = new SquareGrid(map.map,this->scene, this);
    grid->setFocusPolicy(Qt::StrongFocus);
    this->setCentralWidget(grid);
    this->setFocusPolicy(Qt::StrongFocus);
    auto pacman_cords = grid->get_pacman();
    this->pacman = new Pacman(pacman_cords.first, pacman_cords.second, map, view);
    scene->addItem(this->pacman);
    auto ghosts_cords = grid->get_ghosts();
    for (int i = 0; i < (int)ghosts_cords.size(); i++) {
        Ghost *ghost = new Ghost(ghosts_cords[i].first, ghosts_cords[i].second, map);
        this->ghosts.push_back(ghost);
        scene->addItem(this->ghosts[i]);
    }
    this->gamestate = new GameState(this->pacman, this->scene, this->map);
    for (int i = 0; i < (int)this->ghosts.size(); i++) {
        gamestate->add_ghost(*this->ghosts[i]);
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
    for (int i = 0; i < (int)this->ghosts.size(); i++) {
        std::cout << "ghost " << i << std::endl;
        this->ghosts[i]->move(i, *this->scene, this->map, *this->pacman);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
