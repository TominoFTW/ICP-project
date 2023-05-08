#include "gamestate.h"
#include <QTimer>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <iostream>
#include "ghost.h"
#include "pacman.h"
#include "key.h"
#include "map.h"
#include "backend.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include "mainwindow.h"
#include <QDir>
//hello
GameState::GameState(QGraphicsView *view, Backend *backend) : view(view), backend(backend), stop(false){
    this->pacman = new Pacman(backend->get_pacman_start(),backend->map, this->view);
    for (int i = 0; i < (int)backend->get_ghosts_start().size(); i++) {
        Ghost *ghost = new Ghost(backend->get_ghosts_start()[i], this->view);
        connect(this->backend, &Backend::g_move, ghost, &Ghost::move);
        this->add_ghost(*ghost);
    }
    this->end = backend->get_portal_pos();
    // todo ak bude cas prerobit logiku klucov podobne ako ma pacman a ghost a iba ich schovavat ak su zobrate
    for (int i = 0; i < (int)backend->get_keys_pos().size(); i++) {
        Key *key = new Key(backend->get_keys_pos()[i], backend->map);
        this->add_key(*key);
    }
    timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, this, &GameState::update);
    // ???????????????????????????????????????????????????????????????
    connect(this->backend, &Backend::p_move, this->pacman, &Pacman::move);
    timer->start(300);
}
GameState::~GameState(){
    delete this->pacman;
    for (Ghost *ghost : this->ghosts){
        delete ghost;
    }
    for (Key *key : this->keys){
        delete key;
    }
    delete this->timer;
}

void GameState::add_ghost(Ghost &ghost){
    this->ghosts.push_back(&ghost);
}
void GameState::add_key(Key &key){
    this->keys.push_back(&key);
}
void GameState::set_pacman_dir(int direction){
    this->pacman->set_direction(direction);
}
void GameState::update(){
    if (stop) return;
    auto old_position = this->pacman->position;
    backend->pacman_move(*this->pacman);
    for (Ghost *ghost : this->ghosts){
        old_position = ghost->position;
        try{
            backend->ghost_move(*ghost, *this->pacman);
        }
        catch (int e){
            pacman->pacman_end();
            this->stop = true;
            connect(qobject_cast<MainWindow*>(this->view->parent()), &MainWindow::save_replay, this, &GameState::replay_print);
            return;
        }
    }
    for (Key *key : this->keys){
        backend->pick_key(*key, *this->pacman, this->keys);
        key->update();
    }
    if (this->keys.size() == 0){
        this->backend->map->map[this->end.second/50][this->end.first/50]->setBrush(QImage("./textures/misc/targerOpen.png").scaled(50,50));
    }
    try{
        backend->check_win(this->end, this->pacman->position, this->keys.size());
    }
    catch (int e){
        this->stop = true;
        connect(qobject_cast<MainWindow*>(this->view->parent()), &MainWindow::save_replay, this, &GameState::replay_print);
        return;
    }

}

void GameState::replay_print() {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    // std::chrono::hours two_hours(2);
    // now += two_hours; // IDK sometimes it is 2 hours behind
    // Gets current time for replay
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d_%H:%M:%S");
    auto file_name = "./replays/replay-" + oss.str() + ".txt";
    std::ofstream replayfile(file_name);

    // Map print
    replayfile << this->backend->map->map.size()-2 << " " << this->backend->map->map[0].size()-2 << std::endl;
    for (int i = 1; i < this->backend->map->map.size()-1; i++){
        for (int j = 1; j < this->backend->map->map[i].size()-1; j++){
            replayfile << this->backend->map->map[i][j]->type;
        }
        replayfile << std::endl;
    }
    // Pacman print
    replayfile << "pacman" << std::endl;
    for (auto v : this->pacman->movement){
        replayfile << v.first << "," << v.second << " ";
    }
    this->pacman->movement.clear();
    replayfile << std::endl;
    // Ghosts print
    int i = 0;
    for (Ghost *ghost : this->ghosts){
        replayfile << "ghost" << i++ << std::endl;
        for( auto v : ghost->movement){
            replayfile << v.first << "," << v.second << " ";
        }
        replayfile << std::endl;
        ghost->movement.clear();
    }
    replayfile.close();
    QDir directory("./replays");
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
    MainWindow *main_window = qobject_cast<MainWindow*>(this->view->parent());
    main_window->relativePaths2 = relativePaths;
}
bool GameState::stopped(){
    return this->stop;
}
