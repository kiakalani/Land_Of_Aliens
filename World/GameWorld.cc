#include "GameWorld.hh"
#include "../Entity/Entity.hh"
#include "../Camera/Camera.hh"
#include <stdio.h>
#include "../Entity/Entities/Terrain.hxx"
#include "../Display/GameDisplay.hh"
#include "../Game/Entity/Tank.hxx"
GameWorld::GameWorld(): head((EntityNode*)0), gravity(0.098f), tail((EntityNode*)0), terrain((Terrain*)0), player((Tank*)0)
{}

GameWorld::~GameWorld()
{
    while (head)
    {
        EntityNode *cur = head;
        head = head->next;
        delete cur->entity;
        delete cur;
    }
}

void GameWorld::add_entity(Entity *entity)
{
    if (!head)
    {
        head = tail = new EntityNode;
        head->next = NULL;
        head->entity = entity;
    } else
    {
        tail->next = new EntityNode;
        tail = tail->next;
        tail->entity = entity;
        tail->next = NULL;
    }
}


void GameWorld::update()
{
    // First handling collisions:
    for (EntityNode *i = head; i; i = i->next)
    {
        for (EntityNode *j = i->next; j; j = j->next)
        {
            if (i == j || i->entity == terrain || j->entity == terrain) continue;

            i->entity->handle_other(j->entity);
            j->entity->handle_other(i->entity);

            if (i->entity->collides((const Entity*&)j->entity)) {
                i->entity->handle_collision(j->entity);
                j->entity->handle_collision(i->entity);
            }
        }
    } // Not the most efficient but couldn't think of something faster that is also memory efficient
    int c_entities = 0;
    EntityNode *current_nodes = NULL;
    EntityNode **current = &current_nodes;
    EntityNode *n = head;

    while (n)
    {
        ++c_entities;
        EntityNode *cur = n;
        if (!n->next && !(n->entity->is_removed())) tail = n;
        n = n->next;

        if (cur->entity == GameDisplay::make_display()->get_camera()->get_to_follow())
            GameDisplay::make_display()->get_camera()->update();
        
        cur->entity->update();
        
        if (terrain && cur->entity != terrain)
        {
            float terrain_y_val = terrain->get_terrain_height(cur->entity->get_position());
            cur->entity->handle_terrain_collision(terrain_y_val, gravity);
        }

        if (cur->entity->is_terrained())
        {
            
            cur->entity->set_translate_speed(glm::vec3(0.0f, -gravity, 0.0f));
            
        }
        
        if (cur->entity->is_removed())
        {
            if (cur->entity)
            delete cur->entity;
            delete cur;
        }
        else
        {
            if (!(*current))
            {
                *current = cur;
                (*current)->next = NULL;
            }
            else
            {
                (*current)->next = cur;
                current = &((*current)->next);
                (*current)->next = NULL;
            }
        }
    }
    head = current_nodes;
    
}

void GameWorld::render(Camera *c)
{
    glm::mat4 view = c->get_view_mat();
    glm::mat4 projection = c->get_projection_mat();
    glm::mat4 projection_2d = c->get_2d_proj_mat();
    
    for (EntityNode *i = head; i; i = i->next)
    {
        if (!i->entity->is_transparent())
        i->entity->render(view, projection, projection_2d);
    }

    for (EntityNode *i = head; i; i = i->next)
    {
        if (i->entity->is_transparent())
        i->entity->render(view, projection, projection_2d);
    }
}

Tank *GameWorld::get_player() const
{
    return player;
}

void GameWorld::set_event_handlers()
{

}


glm::vec2 GameWorld::random_position() const
{
    return glm::vec2(((float)rand() / RAND_MAX) * terrain->max_x(),
        ((float)rand() / RAND_MAX) * terrain->max_z());
}