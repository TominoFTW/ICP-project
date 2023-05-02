#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "map.h"
#include "map_object.h"
#include "map_grid.h"
#include <QLayout>
#include "pacman.h"

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
    this->setCentralWidget(grid);
    this->setFocusPolicy(Qt::StrongFocus);
    grid->setFocusPolicy(Qt::StrongFocus);
    // TODO:find object in map
    this->pacman = new Pacman(1,9, map);
    scene->addItem(this->pacman);

}


// registering users input with w-s-a-d and arrow keys
void MainWindow::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_W:
        case Qt::Key_Up:
            this->pacman->move(3, *this->scene, this->map);
            std::cout << "up" << std::endl;
            break;
        case Qt::Key_S:
        case Qt::Key_Down:
            this->pacman->move(1, *this->scene, this->map);
            std::cout << "down" << std::endl;
            break;
        case Qt::Key_A:
        case Qt::Key_Left:
            this->pacman->move(2, *this->scene, this->map);
            std::cout << "left" << std::endl;
            break;
        case Qt::Key_D:
        case Qt::Key_Right:
            this->pacman->move(0, *this->scene, this->map);
            std::cout << "right" << std::endl;
            break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
