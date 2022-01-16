#include "Supply.hxx"
#include <stdio.h>
#include "../../World/GameWorld.hh"
#include "Tank.hxx"
Supply::Supply(SupplyType t, const float &val, const float &lon, Entity *p):
Entity(
    GameDisplay::get_geometries()->CYLINDER(),
    GameDisplay::get_loaded_shaders()->ATOM(),
    NULL
),
    type(t), value(val), longevity(lon), consumer(p)
{
    set_terrained(1);
    if (t == SHELL) texture = GameDisplay::get_loaded_textures()->SPACE_SNAIL_SHELL();
    else if (t == STONE) texture = GameDisplay::get_loaded_textures()->SPACE_STONE_MONSTER_BODY();
    else if (t == DRAGON_SKIN) texture = GameDisplay::get_loaded_textures()->DRAGON_BODY();
    else if (t == WOOD) texture = GameDisplay::get_loaded_textures()->TREE_BODY();
    else if (t == FUEL) texture = GameDisplay::get_loaded_textures()->SPACE_SNAIL_BODY();
    else texture = GameDisplay::get_loaded_textures()->LEADER_CROWN();

    set_scale(glm::vec3(3.0f, 6.0f, 3.0f));
    set_collision_width(3.0f);
    set_collision_height(3.0f);
    set_collision_depth(3.0f);
    appearance_time = glfwGetTime();
    consumer = (Entity*)GameDisplay::make_display()->get_current_game_world()->get_player();


    count_multiples = 200; 

    x_multiples = new float[count_multiples];
    particles = new glm::vec3[count_multiples];
    y_multiples = new float[count_multiples];
    z_multiples = new float[count_multiples];
    for (uint32_t i = 0; i < count_multiples >> 2; ++i) {
        float xmult = (float)rand() / RAND_MAX; // randomized x angle for orbit
        float ymult = (float)rand() / RAND_MAX; // randomized y angle for orbit
        glm::vec3 particle = glm::vec3((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX); // random position for a particle
        float zmult = (float)rand() / RAND_MAX; // randomized z angle for orbi
        for (uint8_t j = 0; j < 4; ++j) // Basically four spheres per orbit
        {
        x_multiples[4 * i + j] = xmult;
        y_multiples[4 * i + j] = ymult;
        particles[4 * i + j] = particle;
        particles[4 * i + j] = glm::normalize(particles[4 *i + j]);
        z_multiples[4 * i + j] = zmult;
        }
    }
    set_count_duplicates(count_multiples + 1); // 1 for the circle in center and 
    // the rest for the circles around the atom

}


void Supply::update()
{
    if (glfwGetTime() - appearance_time >= longevity)
        remove();
    Entity::update();
}

void Supply::handle_collision(Entity *e)
{
    if (e == (Entity*)GameDisplay::make_display()->get_current_game_world()->get_player())
    {
        Tank *t = GameDisplay::make_display()->get_current_game_world()->get_player();
        switch (type)
        {
            case WOOD:
                t->set_count_wood(t->get_count_wood() + (uint16_t)value);
                break;
            case GOLD:
                t->set_count_gold(t->get_count_gold() + (uint16_t)value);
                break;
            case SHELL:
                t->heal(value);
                break;
            case STONE:
                t->set_count_stone(t->get_count_stone() + (uint16_t)value);
                break;
            case FUEL:
                t->fill_gas(value);
                break;
            case DRAGON_SKIN:
                t->set_count_d_skins(t->get_count_d_skins() + (uint16_t)value);
                break;
        }
        // TODO: Add to the player's stats
        remove();
    }
}

SupplyType Supply::get_type() const
{
    return type;
}

void Supply::handle_terrain_collision(const float &y, const float &g)
{
    if (y >= get_position()[1] - get_scale()[1] * 0.5f)
    {
        set_translate_speed(glm::vec3(0.0f, get_translate_speed()[1], 0.0f));
        glm::vec3 pos = get_position();
        set_translate(glm::vec3(pos[0], y + get_scale()[1], pos[2]));
    }
}

void Supply::render(const glm::mat4 &v, const glm::mat4 &proj, const glm::mat4 &proj_2d) const
{
    setup_render_elems(v, proj, proj_2d);
    for (uint32_t i = 0; i < count_multiples; ++i)
    { // Sending all of the x multiples to the shader
        char name[20];
        sprintf(name, "xmult[%u]", i);
        shader->set_uniform_float(name, x_multiples[i]);
        sprintf(name, "positions[%u]", i);
        shader->set_uniform_vec3(name, particles[i]);
        sprintf(name, "ymult[%u]", i);
        shader->set_uniform_float(name, y_multiples[i]);
        sprintf(name, "zmult[%u]", i);
        shader->set_uniform_float(name, z_multiples[i]);
    }
    setup_render_draw();
}

Supply::~Supply()
{
    delete[] x_multiples;
    delete[] particles;
    delete[] y_multiples;
    delete[] z_multiples;
}