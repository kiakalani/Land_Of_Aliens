#ifndef _STAR_HXX_
#define _STAR_HXX_
#include "../../Entity/HierarchyEntity.hh"

class Star: public HierarchyEntity
{ 
    HierarchyEntity *inner_sphere;
    HierarchyEntity *tips[4];
    // Allies or enemies
    bool friendly;
    bool attacking;

    
    glm::vec3 initial_pos;
    public:
    Star(const bool& = 0);
    ~Star();
    void update();
    void handle_terrain_collision(const float&, const float&);
    void handle_collision(Entity*);

    bool is_friendly() const;
    void set_initial_pos();


    void handle_other(Entity*);
};

#endif