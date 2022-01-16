#ifndef _TREE_HXX_
#define _TREE_HXX_
#include "../../Entity/HierarchyEntity.hh"

class Tree: public HierarchyEntity
{
    HierarchyEntity *leaves[2];

    HierarchyEntity *top[4];

    public:
    Tree();
    void update();
    void handle_terrain_collision(const float&, const float&);
};

#endif

