#ifndef _SUPREME_LEADER_HXX_
#define _SUPREME_LEADER_HXX_
#include "../../Entity/HierarchyEntity.hh"
class SupremeLeader: public HierarchyEntity
{
    private:
    float last_bullet;
    HierarchyEntity *legs[3];
    HierarchyEntity *hands[2];
    HierarchyEntity *head;
    HierarchyEntity *crown_body[8];
    HierarchyEntity *crown_top[4];

    public:
    SupremeLeader();
    void update();
    void handle_terrain_collision(const float&, const float&);

    // Attacking allies
    void handle_collision(Entity*);
    void handle_other(Entity*);
};
#endif
