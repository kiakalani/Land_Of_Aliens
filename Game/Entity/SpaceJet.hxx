#ifndef _SPACE_JET_HXX_
#define _SPACE_JET_HXX_
#include "../../Entity/HierarchyEntity.hh"
class SpaceJet: public HierarchyEntity
{
    HierarchyEntity *top;
    // Last go or down invoking
    float last_time;
    // direction the y should go
    float y_dir;
    // shoots towards allies
    void shoot();
    float y_val;
    public:
    SpaceJet();

    void update();
    // for shooting and handling other tasks related to other entities
    void handle_other(Entity*);
    void handle_terrain_collision(const float&, const float&);
};
#endif