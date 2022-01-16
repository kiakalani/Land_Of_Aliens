#include "Tree.hxx"
#include "Supply.hxx"
#include "../../World/GameWorld.hh"
#include "../../World/GamePage.hxx"
#include "Tank.hxx"
#include <stdio.h>
Tree::Tree(): HierarchyEntity(GameDisplay::make_display()->get_geometries()->CYLINDER(),
    (Shader*)GameDisplay::make_display()->get_loaded_shaders()->TEXTURED(),
    GameDisplay::make_display()->get_loaded_textures()->TREE_BODY())
{
    set_terrained(1);
    set_scale(glm::vec3(4.0f, 20.0f, 4.0f));
    set_collision_width(4.0f);
    set_collision_height(22.0f);
    set_collision_depth(4.0f);
    Geometry *sphere = GameDisplay::make_display()->get_geometries()->SPHERE();
    Geometry *cylinder = GameDisplay::make_display()->get_geometries()->CYLINDER();
    Shader *procedural = (Shader*)GameDisplay::make_display()->get_loaded_shaders()->TEXTURED();
    Texture *top_tx = GameDisplay::make_display()->get_loaded_textures()->TREE_TOP();
    Texture *body_tx =  GameDisplay::make_display()->get_loaded_textures()->TREE_BODY();
    for (uint8_t i = 0; i < 2; ++i)
    {
        leaves[i] = new HierarchyEntity(cylinder, procedural, body_tx);
        leaves[i]->set_translate(glm::vec3(0.75f + (i * -1.5), i * -0.25f, 0.0f));
        add_child_node(leaves[i]);
        leaves[i]->set_scale(glm::vec3(0.125f, 0.85f, 0.125f));
        float mult = i ? -1 : 1;
        leaves[i]->set_orientation(glm::angleAxis(glm::pi<float>() * 0.65f * mult, glm::vec3(0.0f, 0.0f, 1.0f)));

    }
    set_entity_team(ENEMY);

    for (uint8_t i = 0; i < 4; ++i)
    {
        top[i] = new HierarchyEntity(sphere, procedural, top_tx);
        add_child_node(top[i]);
        if (!i)
        {
            top[i]->set_scale(glm::vec3(2.0f, 0.2f, 2.0f));
            top[i]->set_translate(glm::vec3(0.0f, 0.55f, 0.0f));
        }
        else
        {
            top[i]->set_scale(glm::vec3(0.75f, 0.4f, 0.75f));
            top[i]->set_translate(glm::vec3(-2.0f + i * (1.0f), 0.55f, 0.0f + 1.0f * (i == 2)));
        }
        
    }
}

void Tree::update()
{
    HierarchyEntity::update();
    if (health <= 0.0f)
    {
        
        // Reward of the player
        Supply *s = new Supply(WOOD, 15.0f, 15.0f);
        s->set_translate(glm::vec3(get_position()[0], get_position()[1], get_position()[2]));
        GameDisplay::make_display()->get_current_game_world()->add_entity(s);  
        remove();

        // Spawn another tree
        Tree *another_one = new Tree;
        glm::vec2 rand_pos = GameDisplay::make_display()->get_current_game_world()->random_position();
        another_one->set_translate(glm::vec3(rand_pos[0], 20.0f, rand_pos[1]));
        GameDisplay::make_display()->get_current_game_world()->add_entity(another_one);
    }
    
    
}

void Tree::handle_terrain_collision(const float &y, const float &gravity)
{
    if (y > get_position()[1] - get_scale()[1] *0.5f)
    {
        glm::vec3 position = get_position();
        set_translate(glm::vec3(position[0], y + get_scale()[1] * 0.5f, position[2]));
        set_translate_speed(glm::vec3(0.0f, -get_translate_speed()[1], 0.0f));
    }
    HierarchyEntity::handle_terrain_collision(y, gravity);
}
