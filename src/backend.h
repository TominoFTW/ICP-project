#ifndef BACKEND_H
#define BACKEND_H
#include "map.h"
#include <string>
#include <vector>
#include <utility>
#include "pacman.h"
#include "ghost.h"
class Backend
{
public:
    Backend();
    Map *load_map(std::string filename);
    void pacman_move(Pacman &pacman);
    void ghost_move(Ghost &ghost, Pacman &pacman);
    void check_collision(Pacman &pacman, Ghost &ghost);
    void check_win(Map *map);
    void pick_key(Map *map);
private:
    Map *map;
};




#endif // BACKEND_H