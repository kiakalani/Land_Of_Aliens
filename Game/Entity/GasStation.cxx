#include "GasStation.hxx"
#include "Tank.hxx"
#include "../../World/GameWorld.hh"
GasStation::GasStation():
HierarchyEntity(
    GameDisplay::get_geometries()->CYLINDER(),
    GameDisplay::get_loaded_shaders()->METAL(),
    GameDisplay::get_loaded_textures()->GAS_STATION()
)
{
    Geometry *cylinder = GameDisplay::get_geometries()->CYLINDER();
    Geometry *sphere = GameDisplay::get_geometries()->SPHERE();
    Shader *procedural = GameDisplay::get_loaded_shaders()->PROCEDURAL();
    set_terrained(1);
    set_scale(glm::vec3(10.0f, 14.0f, 10.0f));
    set_collision_width(10.0f);
    set_collision_height(14.0f);
    set_collision_depth(10);

    bottom = new HierarchyEntity(cylinder, GameDisplay::get_loaded_shaders()->COLORED(), NULL);
    bottom->set_uni_color(glm::vec4(0.3, 0.01, 0.0, 1.0));
    bottom->set_scale(glm::vec3(2.0f, 0.05f, 2.0f));
    bottom->set_translate(glm::vec3(0.0f, -0.5f, 0.0f));
    add_child_node(bottom);
    
    for (uint8_t i = 0; i < 3; ++i)
    {
        heads[i] = new HierarchyEntity(sphere, GameDisplay::get_loaded_shaders()->COLORED(), NULL);
        heads[i]->set_uni_color(glm::vec4(0.3, 0.01, 0.0, 1.0));
        heads[i]->set_translate(glm::vec3(-0.5f + i * 0.5f, 0.5f, 0.0f));
        heads[i]->set_scale(glm::vec3(0.25, 0.125 * 0.5, 0.25));
        add_child_node(heads[i]);
    }

    nozel_body = new HierarchyEntity(cylinder, GameDisplay::get_loaded_shaders()->COLORED(), NULL);
    nozel_body->set_translate(glm::vec3(0.5f, 0.5f, 0.0f));
    nozel_body->set_scale(glm::vec3(1.0f, 0.02f, 0.02f));
    nozel_body->set_uni_color(glm::vec4(0.2, 0.2, 0.2, 1.0));
    add_child_node(nozel_body);

    nozel = new HierarchyEntity(cylinder, GameDisplay::get_loaded_shaders()->COLORED(), NULL);
    nozel->set_uni_color(glm::vec4(0.2, 0.2, 0.2, 1.0));
    nozel->set_scale(glm::vec3(0.02, 30.0f, 1.0f));
    nozel->set_translate(glm::vec3(0.55f, -15.0f, 0.0f));
    nozel_body->add_child_node(nozel);

    nozel_head = new HierarchyEntity(sphere, GameDisplay::get_loaded_shaders()->COLORED(), NULL);
    nozel_head->set_scale(glm::vec3(2.0f, 2.0f / (30.0f), 2.0f));
    nozel_head->translate(glm::vec3(0.0f, -0.5f, 0.0f));
    nozel->add_child_node(nozel_head);

    set_entity_team(NEUTRAL);
}


void GasStation::update()
{
    HierarchyEntity::update();
}

void GasStation::handle_terrain_collision(const float &y, const float &gravity)
{
    if (y >= get_position()[1] - get_scale()[1] *0.5f - bottom->get_scale()[1] * get_scale()[1] * 0.5f)
    {
        glm::vec3 position = get_position();
        set_translate(glm::vec3(position[0], y + get_scale()[1] * 0.5f + bottom->get_scale()[1] * get_scale()[1] * 0.5f, position[2]));
        set_translate_speed(glm::vec3(0.0f, -get_translate_speed()[1], 0.0f));
    }
    HierarchyEntity::handle_terrain_collision(y, gravity);
}


void GasStation::answer_call()
{
    Tank *p = GameDisplay::make_display()->get_current_game_world()->get_player();
    set_translate(p->get_position() + glm::vec3(0.0f, 10.0f, 30.0f));
}


void GasStation::refill_tank()
{
    Tank *p = GameDisplay::make_display()->get_current_game_world()->get_player();
    float distance = glm::length(p->get_position() - get_position());
    if (distance <= 15.0f)
    {
        float empty_fuel = p->get_max_fuel() - p->get_fuel();
        float price = empty_fuel * 0.5f;
        if (price >= p->get_count_gold()) 
        {
            price = p->get_count_gold();
            empty_fuel = 2 * p->get_count_gold();
        }
        p->set_count_gold(p->get_count_gold() - (uint16_t)price);
        p->fill_gas(empty_fuel);
    }
}