#ifndef _HIERARCHY_ENTITY_HH_
#define _HIERARCHY_ENTITY_HH_

#include "Entity.hh"
/// <h1> Author: Kia Kalani </h1>
/// <strong> Student ID: 101145220 </strong>
/// <summary>
/// <code>HierarchyEntity</code> class is responsible for creating
/// a hierarchy for creating some shapes. We set the orbit of children
/// to the world transformation of its parent.
/// <strong> Note: </strong> Please refer to the class definition of <code>Entity</code>
/// for further information about the functionality of an entity.
/// </summary>
/// <strong> Last revised: Monday, November 22nd, 2021 </strong>
class HierarchyEntity: public Entity
{
    protected:
    // Node class for adding children
    class HierarchyNode
    {
        public:
        HierarchyNode *next;
        HierarchyEntity *entity;
    };

    HierarchyNode *children_head, *children_tail;

    public:
    HierarchyEntity(Geometry*, Shader*, Texture*);
    ~HierarchyEntity();
    void render(const glm::mat4&, const glm::mat4&, const glm::mat4&) const;
    void update();
    virtual void handle_terrain_collision(const float&, const float&);
    // Adding a child node
    void add_child_node(HierarchyEntity*);
};

#endif
