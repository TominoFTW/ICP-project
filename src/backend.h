#ifndef BACKEND_H
#define BACKEND_H
#include "map.h"
#include <string>
#include <vector>
#include <utility>
#include "pacman.h"
#include "ghost.h"
#include "key.h"
class Backend
{
public:
    Backend();
    Map *load_map(std::string filename);
    void pacman_move(Pacman &pacman);
    void ghost_move(Ghost &ghost, Pacman &pacman);
    void check_collision(Pacman &pacman, Ghost &ghost);
    void check_win(std::pair<int, int> end, std::pair<int, int> pacman, int size);
    void pick_key(Key &key, Pacman &pacman, std::vector<Key*> &keys);
private:
    Map *map;
};




#endif // BACKEND_H