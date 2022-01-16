#include "Star.hxx"
#include "../../Display/GameDisplay.hh"
#include "Supply.hxx"
#include "Tank.hxx"
#include "../../World/GameWorld.hh"
#include <stdio.h>
Star::Star(const bool &f): HierarchyEntity(GameDisplay::get_geometries()->SPHERE(), (Shader*)GameDisplay::get_loaded_shaders()->PLASTIC(),
f ? GameDisplay::get_loaded_textures()->STAR_FACE1() : GameDisplay::get_loaded_textures()->STAR_FACE2())
{
    health = 50.0f;
    friendly = f;
    set_terrained(1);
    Geometry *sphere = GameDisplay::get_geometries()->SPHERE();
    Geometry *cylinder = GameDisplay::get_geometries()->CYLINDER();
    Shader *sh = (Shader*)GameDisplay::get_loaded_shaders()->PROCEDURAL();
    inner_sphere = new HierarchyEntity(sphere, sh, NULL);
    inner_sphere->set_scale(glm::vec3(0.5, 0.5, 0.5));

    set_scale(glm::vec3(5.0f, 5.0f, 5.0f));
    set_collision_width(5.0f);
    set_collision_height(20.0f);
    set_collision_depth(5.0f);

    add_child_node(inner_sphere);
    for (uint8_t i = 0; i < 4; ++i)
    {
        tips[i] = new HierarchyEntity(cylinder, GameDisplay::get_loaded_shaders()->TEXTURED(), 
        f ? GameDisplay::get_loaded_textures()->STAR_BODY1() : GameDisplay::get_loaded_textures()->STAR_BODY2());
        tips[i]->set_orientation(glm::angleAxis((0.25f * (float)i * glm::pi<float>()) , glm::vec3(0.0, 0.0, 1.0)));
        tips[i]->set_scale(glm::vec3(0.5, 5.0, 0.5));
        inner_sphere->add_child_node(tips[i]);
    }
    set_orientation(glm::angleAxis(glm::pi<float>(), glm::vec3(glm::vec3(0.0f, 1.0f, 0.0f))));
    set_entity_team(f ? ALLY : ENEMY);
    if (get_entity_team() == ALLY)
    initial_pos = (GameDisplay::make_display()->get_current_game_world()->get_player()->get_position() - get_position());
    attacking = 0;
}


void Star::set_initial_pos()
{
    initial_pos = (GameDisplay::make_display()->get_current_game_world()->get_player()->get_position() - get_position());
}

void Star::handle_collision(Entity *e)
{
    if (e->get_entity_team() == get_entity_team())
    {
        if (collides((const Entity*&)e))
        {
            translate(glm::vec3(3.0f, 0.0f,3.0f));
            set_initial_pos();
        }
    } else {
        e->take_damage(10.0f);
    }
    Entity::handle_collision(e);
}


void Star::update()
{
    if (health <= 0.0f && get_entity_team() == ENEMY)
    {
        Supply *s = new Supply(GOLD, 5.0f, 10.0f, GameDisplay::make_display()->get_current_game_world()->get_player());
        remove();
        s->set_translate(get_position());
        GameDisplay::make_display()->get_current_game_world()->add_entity(s);
        Star *respawn = new Star(0);
        glm::vec2 rand_pos = GameDisplay::make_display()->get_current_game_world()->random_position();
        respawn->set_translate(glm::vec3(rand_pos[0], 0.0f, rand_pos[1]));
        GameDisplay::make_display()->get_current_game_world()->add_entity(respawn);
    } else if (health <= 0.0f)
    {
        remove();
        printf("DONE FOR\n");
    }
    inner_sphere->rotate(glm::quat(0.01f, glm::vec3(0.0, 0.0f, 1.0f)));
    // FOR NOW TO SEE IF IT WORKS
    if (get_entity_team() == ALLY && !attacking)
    set_translate(GameDisplay::make_display()->get_current_game_world()->get_player()->get_position() + initial_pos);
    attacking = 0;
    HierarchyEntity::update();
}

void Star::handle_other(Entity *e)
{
    if (e->get_entity_team() != get_entity_team() && (e->get_entity_team() == ALLY || e->get_entity_team() == ENEMY))
    {
        if (glm::length(e->get_position() - get_position()) < 300.0f)
        {
            attacking = 1;
            translate(5.0f * glm::normalize(e->get_position() - get_position()) );
        }
    }
}

void Star::handle_terrain_collision(const float &y, const float &g)
{
    if (y >= get_position()[1] - 8.0)
    {
        glm::vec3 pos = get_position();
        set_translate(glm::vec3(pos[0], y + 8.0, pos[2]));
        set_translate_speed(glm::vec3(0.0f, -get_translate_speed()[1], 0.0f));
        HierarchyEntity::handle_terrain_collision(y, g);
    }
}
