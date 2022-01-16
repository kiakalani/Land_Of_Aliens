#ifndef _SPACE_DRAGON_HXX_
#define _SPACE_DRAGON_HXX_
#include "../../Entity/HierarchyEntity.hh"
class SpaceDragon: public HierarchyEntity
{
    private:
    HierarchyEntity *head;
    HierarchyEntity *horns[4];
    HierarchyEntity *legs[8];
    HierarchyEntity *tail;
    HierarchyEntity *tail_tip;
    float last_time;
    float prev_time;
    public:
    SpaceDragon();

    void update();
    // Moves legs and tail
    void dance();

    void handle_terrain_collision(const float&, const float&);
    // if close enough dragon would start shooting
    void handle_other(Entity*);
    void fire();
}; 
#endif
