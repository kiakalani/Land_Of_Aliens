#include "SpaceDragon.hxx"
#include "Supply.hxx"
#include "Tank.hxx"
#include "../../World/GameWorld.hh"
#include "Weapons/Bullet.hxx"
#include <stdio.h>
SpaceDragon::SpaceDragon():
HierarchyEntity(
    GameDisplay::make_display()->get_geometries()->CYLINDER(),
    GameDisplay::make_display()->get_loaded_shaders()->PLASTIC(),
    GameDisplay::get_loaded_textures()->DRAGON_BODY()
)
{
    set_terrained(1);

    Geometry *cylinder = GameDisplay::make_display()->get_geometries()->CYLINDER();
    Geometry *sphere = GameDisplay::get_geometries()->SPHERE();
    Shader *procedural = GameDisplay::get_loaded_shaders()->PROCEDURAL();
    Shader *textured = GameDisplay::get_loaded_shaders()->TEXTURED();

    set_scale(glm::vec3(10.0f, 30.0f, 10.0f));
    set_orientation(glm::angleAxis(glm::pi<float>() * 0.5f, glm::vec3(0.0f, 0.0f, 1.0f)));
    set_collision_width(45.0f);
    set_collision_height(10.0f);
    set_collision_depth(10.0f);
    head = new HierarchyEntity(sphere, textured, 
    GameDisplay::get_loaded_textures()->DRAGON_HEAD());
    head->set_translate(glm::vec3(0.0f, -0.65f, 0.0f));
    head->set_scale(glm::vec3(1.0f, 0.333f, 1.0f));
    add_child_node(head);

    Texture *body = GameDisplay::get_loaded_textures()->DRAGON_BODY();

    for (uint8_t i = 0; i < 4; ++i)
    {
        horns[i] = new HierarchyEntity(cylinder, textured, body);
        head->add_child_node(horns[i]);
        horns[i]->set_translate(glm::vec3(0.6f, 0.3f, -0.40f + i * 0.25f));
        horns[i]->set_scale(glm::vec3(0.1f, 1.5f, 0.1f));
        horns[i]->set_orientation(glm::angleAxis(-glm::pi<float>() * 0.25f, glm::vec3(0.0f, 0.0f, 1.0f)));
    }

    for (uint8_t i = 0; i < 8; ++i)
    {
        legs[i] = new HierarchyEntity(sphere, textured, body);

        add_child_node(legs[i]);
        legs[i]->set_scale(glm::vec3(0.25f, 0.111f, 0.25f));
        legs[i]->set_translate(glm::vec3(-0.5f, -0.4f +  0.25f * (i % 4), -0.5f + (i / 4)));
    }

    tail = new HierarchyEntity(cylinder, textured, body);
    tail->set_translate(glm::vec3(0.0f, 0.75f, 0.0f));
    tail->set_scale(glm::vec3(0.25f, 0.5f, 0.25f));
    add_child_node(tail);

    tail_tip = new HierarchyEntity(sphere, textured, body);
    tail_tip->set_translate(glm::vec3(0.0f, 0.6f, 0.0f));
    tail_tip->set_scale(glm::vec3(1.0f, 0.2f, 1.0f));
    tail->add_child_node(tail_tip);

    tail->set_orbit(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.75f, 0.0f)));

    last_time = prev_time = 0.0f;

    set_entity_team(ENEMY);
    health = 150.0f;
}

void SpaceDragon::fire()
{
    float pi = glm::pi<float>();
    if (glfwGetTime() - prev_time >= 1.0f)
    for (uint8_t i = 0; i < 16; ++i)
    {
        float angle = (pi * (1 + i / 4)) / float(i % 4);
        Bullet *b = new Bullet(10, glm::vec3(glm::cos(angle), 0.0f, glm::sin(angle)), 5.0f, this);
        prev_time = glfwGetTime();
        b->set_translate(get_position());
        b->set_power(50);
        GameDisplay::make_display()->get_current_game_world()->add_entity(b);
    }
}

void SpaceDragon::update()
{
    if (health <= 0.0f)
    {
        remove();
        Supply *s = new Supply(DRAGON_SKIN, 10.0f, 10.0f, GameDisplay::make_display()->get_current_game_world()->get_player());
        s->set_translate(get_position());
        GameDisplay::make_display()->get_current_game_world()->add_entity(s);
        SpaceDragon *d = new SpaceDragon;
        glm::vec2 rand_pos = GameDisplay::make_display()->get_current_game_world()->random_position();
        d->set_translate(glm::vec3(rand_pos[0], 0.0f, rand_pos[1]));
        GameDisplay::make_display()->get_current_game_world()->add_entity(d);
        // Todo: Add the elements of the game, another space dragon and dragon skin
    }
    
    dance();
    HierarchyEntity::update();
}

void SpaceDragon::dance()
{
    last_time = glfwGetTime();
    float angle = -(float)glm::cos(last_time * 5.0f);
    if (angle > glm::pi<float>() * 0.5f && angle < glm::pi<float>()) angle *= -1;

    for (uint8_t i = 0; i < 8; ++i)
    {
        legs[i]->set_orientation(glm::angleAxis(angle, glm::vec3(0.0f, 0.0f, 1.0f)));
    }

    tail->set_orientation(glm::angleAxis(angle * 0.5f, glm::vec3(1.0f, 0.0f, 0.0f)));
}

void SpaceDragon::handle_terrain_collision(const float &y, const float &gravity)
{
    if (y >= get_position()[1] - get_scale()[0] * 0.5f - legs[0]->get_scale()[0] * 4.0f)
    {
        glm::vec3 position = get_position();
        set_translate_speed(glm::vec3(0.0f, -get_translate_speed()[1], 0.0f));
        set_translate(glm::vec3(position[0], y + get_scale()[0] * 0.5f + legs[0]->get_scale()[0] * 4.0f, position[2]));
        HierarchyEntity::handle_terrain_collision(y, gravity);
    }
}

void SpaceDragon::handle_other(Entity *e)
{
    if (e == GameDisplay::make_display()->get_current_game_world()->get_player())
    {
        if (glm::length(e->get_position() - get_position()) <= 500.0f)
        fire();
    }
}