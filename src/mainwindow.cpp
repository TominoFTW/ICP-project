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
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDialog>
#include <QPushButton>
#include <QDir>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Pacmun");
    bool replay = false;
    // todo skusit toto upravit
    this->backend = new Backend();
    this->backend->load_map("./examples/map-01.txt");
    //Map *map = new Map("./examples/map-01.txt");
    this->scene = new MainScene(backend);
    if (replay) {
        this->replay = new Replay(this, this->scene);
        // IDK je to sracka
    }
    //####################################################################################################
    QMenuBar *menuBar = new QMenuBar(this);
    
    // Add a menu to the menu bar
    QMenu *fileMenu = menuBar->addMenu(tr("Menu"));
    
    // Add an action to show the map levels dialog
    QAction *mapLevelsAction = new QAction(tr("Maps"), this);
    fileMenu->addAction(mapLevelsAction);
    connect(mapLevelsAction, &QAction::triggered, this, &MainWindow::showMapLevelsDialog);
    QDir directory("./examples");

    QStringList nameFilters;
    nameFilters << "*.txt"; // Example: load only txt and pdf files

    // Get a list of file names in the directory matching the filters
    QStringList files = directory.entryList(nameFilters, QDir::Files);

    // Loop over the list of files and store their relative paths
    QStringList relativePaths;
    foreach(QString file, files) {
        QString relativePath = directory.relativeFilePath(file);
        relativePaths << relativePath;
        qDebug() << relativePath;
    }
    this->relativePaths = relativePaths;
    // Add a separator and an exit action to the menu
    fileMenu->addSeparator();
    
    
    // Set the menu bar as the main window's menu bar
    setMenuBar(menuBar);
    //####################################################################################################
    this->view = new QGraphicsView(this->scene, this);
    // toto nezvacsuje sa okno :)
    view->setFixedSize((int)this->backend->map->map.size()*50+10, (int)this->backend->map->map[0].size()*50+10);
    this->setFixedSize((this->backend->map->width+2)*50+10, (this->backend->map->height+2)*50+35);
    this->setCentralWidget(view);
    view->setFocusPolicy(Qt::StrongFocus);
    this->setFocusPolicy(Qt::StrongFocus);
    view->setFocusPolicy(Qt::NoFocus);
    this->gamestate = new GameState(view, backend);
}

void MainWindow::showMapLevelsDialog()
{
    // Create a dialog to show the map levels
    QDialog *mapLevelsDialog = new QDialog(this);
    mapLevelsDialog->setWindowTitle(tr("Select Map Level"));
    QVBoxLayout *layout = new QVBoxLayout(mapLevelsDialog);
    
    // Add a button for each map level
    for (int i = 0; i < this->relativePaths.size(); i++) {
        QPushButton *levelButton = new QPushButton(tr("Map Level %1").arg(i+1), mapLevelsDialog);
        connect(levelButton, &QPushButton::clicked, this, [this, i]() {
            // Handle the button click by loading the selected map level
            delete this->gamestate;
            delete this->scene;
            backend->load_map("./examples/" + this->relativePaths[i].toStdString());
            this->scene = new MainScene(backend,this);
            this->view->setScene(this->scene);
            this->gamestate = new GameState(this->view, backend);
        });
        layout->addWidget(levelButton);
    }
    
    // Set the dialog size and show it
    mapLevelsDialog->setFixedSize(200, 50*3);
    mapLevelsDialog->exec();
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
    delete this->view;
    delete this->backend;
}
