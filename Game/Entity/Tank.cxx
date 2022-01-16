#include "Tank.hxx"
#include "../../Camera/Camera.hh"
#include "Weapons/Bullet.hxx"
#include "../../World/GameWorld.hh"
#include <stdio.h>
#include "Star.hxx"
typedef glm::vec3 vec3;

// #define rotation(angle, x, y, z) glm::angleAxis(angle, glm::vec3(x, y, z))

glm::quat rotation(float angle, float x, float y, float z) 
{
    return glm::angleAxis(glm::radians(angle), glm::vec3(x, y, z));
}
Tank::Tank(): HierarchyEntity(GameDisplay::get_geometries()->SPHERE(), 
(Shader*)GameDisplay::get_loaded_shaders()->METAL(),
 GameDisplay::make_display()->get_loaded_textures()->TANK_BODY())
{
    set_entity_team(ALLY);
    set_terrained(1);
    Geometry *cylinder = GameDisplay::get_geometries()->CYLINDER();
    Geometry *sphere = GameDisplay::get_geometries()->SPHERE();
    Shader *sh = (Shader*)GameDisplay::get_loaded_shaders()->PROCEDURAL();
    
    Shader *colored = GameDisplay::get_loaded_shaders()->COLORED();
    Shader *textured = GameDisplay::get_loaded_shaders()->TEXTURED();

    for (uint8_t i = 0; i < 8; i++) { // handling each wheel
        wheels[i] = new HierarchyEntity(cylinder, textured, GameDisplay::get_loaded_textures()->TANK_TIRE());
        add_child_node(wheels[i]);
        wheels[i]->set_scale(vec3(0.25, 0.1, 0.25));
        wheels[i]->translate(vec3(0.4 - (i % 4) * 0.26, -0.30, -0.5 + i / 4));
        wheels[i]->set_orientation(rotation(90.0, 1.0, 0.0, 0.0));
    }
    gun_pipe = new HierarchyEntity(cylinder, GameDisplay::get_loaded_shaders()->METAL(), GameDisplay::get_loaded_textures()->TANK_WINDOW());
    add_child_node(gun_pipe);

    window = new HierarchyEntity(cylinder, GameDisplay::get_loaded_shaders()->PLASTIC(), GameDisplay::get_loaded_textures()->TANK_WINDOW());
    gun_pipe->add_child_node(window);

    anthena = new HierarchyEntity(cylinder, colored, NULL);
    gun_pipe->add_child_node(anthena);
    anthena->set_uni_color(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

    anthena_tip = new HierarchyEntity(sphere, colored, NULL);
    anthena->add_child_node(anthena_tip);
    anthena_tip->set_uni_color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    Texture *body = GameDisplay::get_loaded_textures()->TANK_BODY();
    door = new HierarchyEntity(sphere, textured, body);
    window->add_child_node(door);

    door_tip = new HierarchyEntity(sphere, textured, body);
    door->add_child_node(door_tip);

    set_scale(vec3(5.0, 3.0, 4.0));
    set_collision_width(5.0f);
    set_collision_height(5.0f);
    set_collision_depth(4.0f);

    gun_pipe->set_orientation(rotation(90.0, 0.0, 0.0, 1.0));
    gun_pipe->set_scale(vec3(0.5, 2.0, 1.0));
    gun_pipe->translate( glm::vec3(0.375, -0.9, 0.0));

    window->set_scale(vec3(0.5, 0.5, 0.5));
    window->translate(vec3(0.75, 0.15, 0.0));
    door->set_scale(vec3(1.25, 0.40, 1.0));
    door->translate(vec3(0.5, 0.0, 0.0));

    anthena->translate(vec3(0.6, 0.45, 0.0));
    anthena->set_orientation(rotation(270.0, 0.0, 0.0, 1.0));
    anthena->set_scale(vec3(0.01, 3.0, 0.04));
    anthena_tip->set_scale(vec3(2.0, 0.05, 2.0));
    anthena_tip->translate(vec3(0.0, 0.5, 0.0));

    set_orientation(glm::angleAxis(-glm::pi<float>() / 2, glm::vec3(0.0f, 1.0f, 0.0f)));
    gun_pipe->set_orbit(glm::translate(glm::mat4(1.0), glm::vec3(-0.7, 0.8, 0.0)));
    up_rot = 0.0f;

    rotation_spd = 0.0f;
    forward_spd = 0.0f;

    max_health = health = 500.0f;

    fuel = max_fuel = 100.0f;
    count_gold = count_stars = count_stone = count_wood = count_bullets = count_d_skins = 0;
    count_bullets = 30;
    bullet_dmg = 50.0;
    count_gold = 500;
    count_stone = 1;
    count_d_skins = 1;

    boosting = 0;
}

float Tank::get_fuel() const
{
    return fuel;
}

float Tank::get_max_fuel() const
{
    return max_fuel;
}

void Tank::handle_terrain_collision(const float &y, const float &gravity)
{
    if (get_position()[1] - get_scale()[1] <= y)
    {
        glm::vec3 new_translate = glm::vec3(get_position()[0], y + get_scale()[1], get_position()[2]);
        set_translate(new_translate);
        set_translate_speed(glm::vec3(0.0f, -get_translate_speed()[1], 0.0f));
        glm::vec3 speed = get_translate_speed();
        HierarchyEntity::handle_terrain_collision(y, gravity);

    }
}

void Tank::rotate_gun_pipe(const float &angle)
{
    float a = boosting ? 10.0f * angle : angle;
    gun_pipe->rotate(glm::angleAxis(a, glm::vec3(1.0f, 0.0f, 0.0f)));
    for (uint8_t i = 0; i < 8; ++i) wheels[i]->rotate(glm::angleAxis(-a, glm::vec3(0.0f, 0.0f, 1.0f)));
    Camera *cam = GameDisplay::make_display()->get_camera();
    float cam_distance = glm::length(get_position() + cam->get_position());
    cam->set_rotation_addition(glm::vec3(a, 0.0f, a));
}


void Tank::update()
{

    glm::quat rev_or = gun_pipe->get_orientation();
    glm::quat rev = glm::quat(rev_or.w, rev_or.y, rev_or.x, rev_or.z);
    glm::vec3 fwd_pos = rev * glm::vec3(0.0f, 0.0f, 1.0f);
    set_translate_speed(glm::vec3(-get_translate_speed()[0], 0.0f, -get_translate_speed()[2]));
    set_translate_speed((boosting ? 10 : 1) * forward_spd * fwd_pos);
    rotate_gun_pipe(rotation_spd);
    if (forward_spd != 0.0f || rotation_spd != 0.0f)
    fuel -= boosting ? 0.2f : 0.01f;

    HierarchyEntity::update();

}

void Tank::shoot()
{
    if (count_bullets > 0)
    {
        glm::quat rev_or = gun_pipe->get_orientation();
        glm::quat rev = glm::quat(rev_or.w, rev_or.y, rev_or.x, rev_or.z);
        glm::vec3 fwd_pos = rev * glm::vec3(0.0f, 0.0f, 1.0f);

        Bullet *bullet = new Bullet(10.0f, fwd_pos, 5.0f, this);
        bullet->set_translate(get_position() + (get_scale() + gun_pipe->get_scale() * 0.5f) * glm::vec3(0.0f, 1.0f, 0.0f));
        bullet->set_power(bullet_dmg);

        GameDisplay::make_display()->get_current_game_world()->add_entity(bullet);
        --count_bullets;
    }
    
}

void Tank::handle_collision(Entity *e)
{
    if (e->get_entity_team() == ENEMY)
    {
        e->take_damage(10.0f);
    } else if (get_entity_team() == e->get_entity_team() && get_entity_team() == ALLY)
    {
        e->set_translate(e->get_position() + glm::vec3(10.0f, 0.0f, 10.0f));
    }
    Entity::handle_collision(e);
}

void Tank::set_forward_spd(const float &f)
{
    forward_spd = f;
}

void Tank::set_rotation_spd(const float &r)
{
    rotation_spd = r;
}

float Tank::get_fuel_percent() const
{
    return (fuel / max_fuel) * 100.0f;
}

float Tank::get_health_percent() const
{
    return (health / max_health) * 100.0f;
}

uint16_t Tank::get_count_bullets() const
{
    return count_bullets;
}

uint16_t Tank::get_count_d_skins() const
{
    return count_d_skins;
}

uint16_t Tank::get_count_gold() const
{
    return count_gold;
}

uint16_t Tank::get_count_wood() const{
    return count_wood;
}

uint16_t Tank::get_count_stone() const
{
    return count_stone;
}

uint16_t Tank::get_count_stars() const
{
    return count_stars;
}

void Tank::set_count_bullets(const uint16_t &b)
{
    count_bullets = b;
}

void Tank::set_count_d_skins(const uint16_t &d)
{
    count_d_skins = d;
}

void Tank::set_count_gold(const uint16_t &g)
{
    count_gold = g;
}

void Tank::set_count_wood(const uint16_t &w)
{
    count_wood = w;
}

void Tank::set_count_stone(const uint16_t &s)
{
    count_stone = s;
}

void Tank::set_count_stars(const uint16_t &ss)
{
    count_stars = ss;
}

void Tank::hire_rebel()
{
    if (count_gold >= 50)
    {
        count_gold -= 50;
        count_stars += 1;
    }
}

void Tank::use_rebel()
{
    if (count_stars)
    {
        --count_stars;
        Star *fr = new Star(1);
        fr->set_translate(get_position());
        GameDisplay::make_display()->get_current_game_world()->add_entity(fr);
    }
}

void Tank::heal(const float &h)
{
    if (health + h >= max_health) health = max_health;
    else health += h;
}

void Tank::fill_gas(const float &g)
{
    if (fuel + g >= max_fuel) fuel = max_fuel;
    else fuel += g;
}

float Tank::get_health() const
{
    return health;
}

float Tank::get_max_health() const
{
    return max_health;
}

float Tank::get_bullet_dmg() const
{
    return bullet_dmg;
}

void Tank::boost()
{
    boosting = 1;
}

void Tank::stop_boosting()
{
    boosting = 0;
}

void Tank::create_bullet()
{
    if (count_d_skins >= 1 && count_stone >= 1)
    {
        count_bullets += 1;
        --count_d_skins;
        --count_stone;
    }
}

void Tank::set_max_health(const float &f)
{
    max_health = f;
}
void Tank::set_health(const float &f)
{
    health = f;
}
void Tank::set_bullet_damage(const float &f)
{
    bullet_dmg = f;
}
void Tank::set_max_fuel(const float &f)
{
    max_fuel = f;
}
void Tank::set_fuel(const float &f)
{
    fuel = f;
}


void Tank::upgrade_fuel()
{
    if (count_gold >= 50.0f)
    {
        max_fuel += 5.0f;
        count_gold -= 50.0f;
    }
}

void Tank::upgrade_bullet()
{
    if (count_gold >= 50.0f)
    {
        bullet_dmg += 10.0f;
        count_gold -= 50.0f;
    }
}

void Tank::upgrade_health()
{
    if (count_gold >= 50.0f)
    {
        max_health += 5.0f;
        count_gold -= 50.0f;
    }
}