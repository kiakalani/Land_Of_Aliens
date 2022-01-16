#ifndef _SPACE_STONE_MONSTER_
#define _SPACE_STONE_MONSTER_
#include "../../Entity/HierarchyEntity.hh"
#include <stdint.h>
class SpaceStoneMonster: public HierarchyEntity
{
    HierarchyEntity *head;
    HierarchyEntity *shoulders[2];
    HierarchyEntity *arms[2];
    HierarchyEntity *hands[2];
    HierarchyEntity *bottom;
    HierarchyEntity *legs[2];
    HierarchyEntity *feet[2];

    // For dancing
    float last_time;
    int32_t last_time_int;
    bool left_dancing;

    public:
    SpaceStoneMonster();
    void update();
    void handle_terrain_collision(const float&, const float&);

    void handle_collision(Entity*);
    void handle_other(Entity*);
    // moving legs and shoulders
    void dance();
};
#endif
