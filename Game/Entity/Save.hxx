#ifndef _SAVE_HXX_
#define _SAVE_HXX_
#include "../../Entity/Entity.hh"
#define SAVE_FILE "../../Save/save.bin"
class Tank;
class Save: public Entity
{
    // saves the tank information into save binary file
    void save_tank();
    public:
    Save();
    void save_game(); 
    // handles terrain collision
    void handle_terrain_collision(const float&, const float&);
    
    // loads the tank from a file
    static Tank *load_game();
};
#endif