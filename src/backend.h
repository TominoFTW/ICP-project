#ifndef BACKEND_H
#define BACKEND_H
#include "map.h"
#include <string>
#include <vector>
#include <utility>
#include "pacman.h"
#include "ghost.h"
#include "key.h"
class Backend : public QObject
{
    Q_OBJECT
public:
    Backend();
    ~Backend();
    Map *load_map(std::string filename);
    void pacman_move(Pacman &pacman);
    void ghost_move(Ghost &ghost, Pacman &pacman);
    void check_collision(Pacman &pacman, Ghost &ghost);
    void check_win(std::pair<int, int> end, std::pair<int, int> pacman, int size);
    void pick_key(Key &key, Pacman &pacman, std::vector<Key*> &keys);
    std::pair<int,int> get_pacman_start();
    std::vector<std::pair<int,int>> get_ghosts_start();
    std::pair<int,int> get_portal_pos();
    std::vector<std::pair<int,int>> get_keys_pos();
    Map *map;
    signals:
        void p_move(std::pair<int, int> old_position);

};




#endif // BACKEND_H