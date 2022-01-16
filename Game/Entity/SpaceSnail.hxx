#ifndef _SPACE_SNAIL_HXX_
#define _SPACE_SNAIL_HXX_
#include "../../Entity/HierarchyEntity.hh"

class SpaceSnail: public HierarchyEntity // Illumination
{
    HierarchyEntity *head;
    HierarchyEntity *anthenas[2];
    HierarchyEntity *anthena_tips[2];
    HierarchyEntity *legs[6];
    HierarchyEntity *shell;
    // For making the game more interesting moving the snail
    float last_time;
    glm::vec3 mvmt;
    
    public:
    SpaceSnail();

    void update();

    void handle_terrain_collision(const float&, const float&);
};
#endif