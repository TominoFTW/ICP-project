#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "map.h"
#include "map_object.h"
#include "map_grid.h"
#include <QLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Map map;
    SquareGrid *grid = new SquareGrid(map.map, this);
    this->setCentralWidget(grid);
    // funguje aj show grid TODO: pozriet layout co robi
}


// registering users input with w-s-a-d and arrow keys
void MainWindow::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_W:
        case Qt::Key_Up:
            //direction up
            std::cout << "up" << std::endl;
            break;
        case Qt::Key_S:
        case Qt::Key_Down:
            //direction down
            std::cout << "down" << std::endl;
            break;
        case Qt::Key_A:
        case Qt::Key_Left:
            //direction left
            std::cout << "left" << std::endl;
            break;
        case Qt::Key_D:
        case Qt::Key_Right:
            //direction right
            std::cout << "right" << std::endl;
            break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
