#include "HierarchyEntity.hh"
#include <string.h>
HierarchyEntity::HierarchyEntity(Geometry *g, Shader *s, Texture *t): Entity(g, s, t), 
    children_head((HierarchyNode*)0), children_tail((HierarchyNode*)0)
{}

void HierarchyEntity::add_child_node(HierarchyEntity *entity)
{
    if (!children_head)
    {
        children_head = children_tail = new HierarchyNode;
        memset(children_head, 0, sizeof(HierarchyNode));
        children_head->entity = entity;
    }
    else
    {
        children_tail->next = new HierarchyNode;
        memset(children_tail->next, 0, sizeof(HierarchyNode));
        children_tail = children_tail->next;
        children_tail->entity = entity;
    }
}

void HierarchyEntity::render(const glm::mat4 &view, const glm::mat4 &proj, const glm::mat4 &proj2d) const
{
    Entity::render(view, proj, proj2d);
    for (HierarchyNode *i = children_head; i; i = i->next)
    {
        i->entity->render(view, proj, proj2d);
    }

}

void HierarchyEntity::update()
{
    Entity::update();

    glm::mat4 world_trans = calculate_world();
    for (HierarchyNode *i = children_head; i; i = i->next)
    {
        // i->entity->set_orbit();
        i->entity->set_parent(world_trans);
        i->entity->update();
    }
}

void HierarchyEntity::handle_terrain_collision(const float &y, const float &gravity)
{
    glm::mat4 world_trans = calculate_world();
    for (HierarchyNode *i = children_head; i; i = i->next)
    {
        i->entity->set_parent(world_trans);
        i->entity->handle_terrain_collision(y, gravity);
    }
}

HierarchyEntity::~HierarchyEntity()
{
    while (children_head)
    {
        HierarchyNode *n = children_head;
        children_head = children_head->next;
        delete n->entity;
        delete n;
    }
}