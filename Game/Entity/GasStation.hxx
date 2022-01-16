#ifndef _GAS_STATION_HXX_
#define _GAS_STATION_HXX_
#include "../../Entity/HierarchyEntity.hh"

class GasStation: public HierarchyEntity 
{
    HierarchyEntity *heads[3];
    HierarchyEntity *bottom;
    HierarchyEntity *nozel_body;
    HierarchyEntity *nozel;
    HierarchyEntity *nozel_head;

    public:
    GasStation();
    ~GasStation();

    void update();
    void handle_terrain_collision(const float&, const float&);
    // Spawns it in front of player
    void answer_call();
    // refills the tank
    void refill_tank();
}; 
#endif