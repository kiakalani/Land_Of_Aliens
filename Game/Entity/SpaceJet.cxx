#include "SpaceJet.hxx"
#include "Tank.hxx"
#include "../../World/GameWorld.hh"
#include "Weapons/Bullet.hxx"
#include "Supply.hxx"
#include <stdio.h>
SpaceJet::SpaceJet():
HierarchyEntity(
    GameDisplay::make_display()->get_geometries()->SPHERE(),
    GameDisplay::make_display()->get_loaded_shaders()->METAL(),
    GameDisplay::get_loaded_textures()->SPACE_JET_BODY()
)
{
    top = new HierarchyEntity(
        GameDisplay::make_display()->get_geometries()->SPHERE(),
        GameDisplay::make_display()->get_loaded_shaders()->METAL(),
        GameDisplay::get_loaded_textures()->SPACE_JET_HEAD()
    );
    set_terrained(1);
    add_child_node(top);

    set_scale(glm::vec3(5.0f, 2.5f, 5.0f));
    
    // Making it a bit easier for the player
    set_collision_width(7.0f);
    set_collision_depth(5.0f);
    set_collision_height(10.0f);

    top->set_scale(glm::vec3(1.0f, 0.8f, 0.75f));
    top->set_translate(glm::vec3(0.0f, 0.5f, 0.0f));
    top->set_orientation(glm::angleAxis(-glm::pi<float>() * 0.5f, glm::vec3(1.0f, 0.0f, 0.0f)));
    top->rotate(glm::angleAxis(-glm::pi<float>() * 0.5f, glm::vec3(0.0f, 1.0f, 0.0f)));

    set_entity_team(ENEMY);
    y_val = 0.0f;
    last_time = glfwGetTime();
}


void SpaceJet::update()
{
    float cur_time = glfwGetTime();
    if (cur_time - last_time >= 5.0f)
    {
        // Go opposite way
        if (!is_terrained())
        {
            y_dir *= -1.0f;
        }
        last_time = cur_time;
    }

    if (health <= 0.0f)
    {
        remove();
        Supply *s = new Supply(FUEL, 100.0f, 10.0f, GameDisplay::make_display()->get_current_game_world()->get_player());
        s->set_translate(get_position());
        GameDisplay::make_display()->get_current_game_world()->add_entity(s);

    }
    translate(glm::vec3(0.0f, y_dir, 0.0f));
    HierarchyEntity::update();
}


void SpaceJet::shoot()
{
    Tank *player = GameDisplay::make_display()->get_current_game_world()->get_player();

    glm::vec3 travel = glm::normalize(player->get_position() - get_position());
    Bullet *b = new Bullet(10.0f, travel, 5.0f, this);
    b->set_translate(get_position());
    GameDisplay::make_display()->get_current_game_world()->add_entity(b);
    
}

void SpaceJet::handle_other(Entity *e)
{
    float t = glfwGetTime();
    if (e == GameDisplay::make_display()->get_current_game_world()->get_player())
    {
        
        if (glm::length(e->get_position() - get_position()) <= 2000.0f)
        if (glm::mod(t - last_time, 2.0f) <=0.01)
        shoot();
    }
}

void SpaceJet::handle_terrain_collision(const float &y, const float &gravity)
{
    if (y >= get_position()[1] - get_scale()[1] * 0.5f)
    {
        set_terrained(0);
        y_val = y;
        y_dir = -0.1f;
        glm::vec3 position = get_position();
        set_translate(glm::vec3(position[0], y + get_scale()[1] * 0.5f, position[2]));
        set_translate_speed(glm::vec3(0.0f, -get_translate_speed()[1], 0.0f));
    }
    HierarchyEntity::handle_terrain_collision(y, gravity);
}