#include "Bullet.hxx"
#include <stdio.h>
#include "../Supply.hxx"
#include "../../../World/GameWorld.hh"
#include "../../../Display/GameDisplay.hh"
Bullet::Bullet(const float &lspan, const glm::vec3 &forward_dir, const float &bull_sp, Entity *owner):
Entity(
    GameDisplay::get_geometries()->SPHERE(),
    GameDisplay::get_loaded_shaders()->METAL(),
    GameDisplay::get_loaded_textures()->BULLET()
)
{
    forward = forward_dir;
    set_scale(glm::vec3(1.5f, 1.5f, 1.5f));
    set_collision_width(1.5f);
    set_collision_height(1.5f);
    set_collision_depth(1.5f);
    lifespan = lspan;
    creation_time = glfwGetTime();

    bullet_speed = bull_sp;

    set_entity_team(owner->get_entity_team());
    this->owner = owner;
    power = 10.0f;

}


void Bullet::update()
{
    translate(forward * bullet_speed);
    if (glfwGetTime() - creation_time >= lifespan)
    remove();
}

float Bullet::get_collision_radius() const
{
    return 0.5f * get_scale()[1];
}

void Bullet::handle_terrain_collision(const float &y, const float &gravity)
{
    if (y >= get_position()[1] - get_scale()[1])
    {
        remove();
    }
}

void Bullet::handle_collision(Entity *e)
{
    if (e != owner)
    {
        if (e->get_entity_team() != owner->get_entity_team())
        {
            e->take_damage(power);
            remove();
        }
    }
}

void Bullet::set_power(const float &p)
{
    power = p;
}