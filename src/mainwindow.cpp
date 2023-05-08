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
#include <QPushButton>
#include <QGraphicsProxyWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Pacmun");
    // todo skusit toto upravit
    this->backend = new Backend();
    connect(this->backend, &Backend::win, this, &MainWindow::win);
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
    }
    this->relativePaths = relativePaths;
    // Add a separator and an exit action to the menu
    fileMenu->addSeparator();


    // Add an action to show the replay dialog
    QAction *replayAction = new QAction(tr("Replay"), this);
    fileMenu->addAction(replayAction);
    connect(replayAction, &QAction::triggered, this, &MainWindow::showReplayDialog);
    QDir directory2("./replays");

    QStringList nameFilters2;
    nameFilters2 << "*.txt";

    QStringList files2 = directory2.entryList(nameFilters2, QDir::Files);

    QStringList relativePaths2;
    foreach(QString file, files2) {
        QString relativePath = directory2.relativeFilePath(file);
        relativePaths2 << relativePath;
    }
    this->relativePaths2 = relativePaths2;
    fileMenu->addSeparator();
    
    
    // Set the menu bar as the main window's menu bar
    this->setMenuBar(menuBar);
    try{
        this->backend->load_map("./examples/map-01.txt");
    }
    catch (char const* e){
        std::cout << e << std::endl;
        exception_flag = true;
        return;
        
    }
    //Map *map = new Map("./examples/map-01.txt");
    this->scene = new MainScene(backend);
    //####################################################################################################
    this->view = new QGraphicsView(this->scene, this);
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
            this->blockSignals(false);
            this->replay_flag = false;
            if (this->replay != nullptr) {
                delete this->replay;
                this->replay = nullptr;
            }
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
            std::cout << "debug" << std::endl;
            try {
                backend->load_map("./examples/" + this->relativePaths[i].toStdString());
            }
            catch (char const* e){
                std::cout << e << std::endl;
                exception_flag = true;
                return;
            }
            this->scene = new MainScene(backend,this);
            if (this->view == nullptr){
                this->view = new QGraphicsView(this->scene, this);
            }
            this->view->setFixedSize((int)this->backend->map->map.size()*50+10, (int)this->backend->map->map[0].size()*50+10);
            this->setFixedSize((this->backend->map->width+2)*50+10, (this->backend->map->height+2)*50+35);
            this->setCentralWidget(view);
            this->view->setScene(this->scene);
            this->gamestate = new GameState(this->view, backend);
        });
        layout->addWidget(levelButton);
        exception_flag = false;
    }
    
    // Set the dialog size and show it
    mapLevelsDialog->setFixedSize(200, 50*3);
    mapLevelsDialog->exec();
}
void MainWindow::showReplayDialog()
{
    // Create a dialog to show the map levels
    QDialog *replayDialog = new QDialog(this);
    replayDialog->setWindowTitle(tr("Select Replay"));
    QVBoxLayout *layout = new QVBoxLayout(replayDialog);
    
    // Add a button for each map level
    std::cout << this->relativePaths2.size() << std::endl;
    for (int i = 0; i < this->relativePaths2.size(); i++) {
        QPushButton *replayButton = new QPushButton(tr("Replay %1").arg(i+1), replayDialog);
        connect(replayButton, &QPushButton::clicked, this, [this, i]() {
            this->blockSignals(false);
            this->replay_flag = true;
            if (this->replay != nullptr) {
                delete this->replay;
                this->replay = nullptr;
            }
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
            backend->get_replay_map("./replays/" + this->relativePaths2[i].toStdString());
            backend->load_map("./replays/tmp.txt");
            this->scene = new MainScene(backend,this);
            if (this->view == nullptr){
                this->view = new QGraphicsView(this->scene, this);
            }
            this->view->setFixedSize((int)this->backend->map->map.size()*50+10, (int)this->backend->map->map[0].size()*50+10);
            this->setFixedSize((this->backend->map->width+2)*50+10, (this->backend->map->height+2)*50+35);
            this->setCentralWidget(view);
            //#################################################################################
            std::vector<QPushButton*> buttons;
            double buttonWidth = this->scene->width() / 4.0;
            QHBoxLayout* layout = new QHBoxLayout();
            layout->setContentsMargins(0, 0, 0, 0);
            layout->setSpacing(0);
            for (int i = 0; i < 4; i++) {
                QPushButton* button = new QPushButton("Button " + QString::number(i));
                button->setFixedWidth(buttonWidth);
                button->setFixedHeight(25);
                layout->addWidget(button);
                buttons.push_back(button);
            }
            buttons[0]->setText("next [D]");
            buttons[1]->setText("prev [A]");
            buttons[2]->setText("start [W]");
            buttons[3]->setText("end [S]");
            buttons[0]->setShortcut(Qt::Key_D);
            buttons[1]->setShortcut(Qt::Key_A);
            buttons[2]->setShortcut(Qt::Key_W);
            buttons[3]->setShortcut(Qt::Key_S);
            QWidget* widget = new QWidget();
            widget->setLayout(layout);
            QGraphicsProxyWidget* proxyWidget = scene->addWidget(widget);
            proxyWidget->setPos(0, scene->height()-widget->height());
            //#################################################################################
            this->view->setScene(this->scene);

            this->replay = new Replay(this, this->scene, "./replays/" + this->relativePaths2[i].toStdString(), backend, this->view);
            connect(buttons[0], &QPushButton::clicked, this->replay, &Replay::update_forward);
            connect(buttons[1], &QPushButton::clicked, this->replay, &Replay::update_backward);
            connect(buttons[2], &QPushButton::clicked, this->replay, &Replay::update_start);
            connect(buttons[3], &QPushButton::clicked, this->replay, &Replay::update_end);
            remove("./replays/tmp.txt");
        });
        layout->addWidget(replayButton);
    }
    exception_flag = false;
    // Set the dialog size and show it
    replayDialog->setFixedSize(200, 50*3);
    replayDialog->exec();
}

// registering users input with w-s-a-d and arrow keys
void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (!replay_flag and !exception_flag) {
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
            case Qt::Key_C:
                if (this->gamestate->stopped()){
                    emit save_replay();
                    this->blockSignals(true);
                }
                break;
            default:
                return;
        }
    }
}
// void MainWindow::mousePressEvent(QMouseEvent *event)
// {
//     if (event->button() == Qt::LeftButton)
//     {
//         QPoint clickPos = event->pos();
//         qDebug() << "Clicked at (" << clickPos.x() << ", " << clickPos.y() << ")";
//     }
// }
void MainWindow::win(){
    win_scene = new QGraphicsScene();
    QGraphicsTextItem *win_text = new QGraphicsTextItem("Congratulations!");
    QGraphicsTextItem *win_text2 = new QGraphicsTextItem("You have won!");
    QGraphicsTextItem *win_text3 = new QGraphicsTextItem("Press \"C\" to save the replay.");
    win_text->setFont(QFont("Arial", 45));
    win_text2->setFont(QFont("Arial", 25));
    win_text3->setFont(QFont("Arial", 13));
    QRectF textRect = win_text->boundingRect();
    QPointF center(this->view->width() / 2.0 - textRect.width() / 2.0, this->view->height() / 2.0 - textRect.height() / 2.0);
    win_text->setPos(center + QPointF(5, 0));
    textRect = win_text2->boundingRect();
    QPointF center2(this->view->width() / 2.0 - textRect.width() / 2.0, this->view->height() / 2.0 - textRect.height() / 2.0);
    win_text2->setPos(center2 + QPointF(5, 55));
    textRect = win_text3->boundingRect();
    QPointF center3(this->view->width() / 2.0 - textRect.width() / 2.0, this->view->height() / 2.0 - textRect.height() / 2.0+200);
    win_text3->setPos(center3 + QPointF(5, 55));
    // Add the image
    QPixmap image("./textures/misc/winner.png");
    QGraphicsPixmapItem *win_image = new QGraphicsPixmapItem(image);
    win_image->setPos(this->view->width() / 2.0 - image.width() / 2.0 + 5, this->view->height() / 2.0 - image.height() / 2.0 + 165);

    win_scene->addItem(win_text);
    win_scene->addItem(win_text2);
    win_scene->addItem(win_image);
    win_scene->addItem(win_text3);
    this->view->setScene(win_scene);
}
MainWindow::~MainWindow()
{
    delete ui;
    if (this->gamestate != nullptr)
        delete this->gamestate;
    if (this->scene != nullptr)
        delete this->scene;
    if (this->win_scene != nullptr)
        delete this->win_scene;
    delete this->view;
    delete this->backend;
}
