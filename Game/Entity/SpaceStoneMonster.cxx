#include "SpaceStoneMonster.hxx"
#include "Supply.hxx"
#include "Tank.hxx"
#include "../../World/GameWorld.hh"
#include "../../Entity/Entities/SphereExplosion.hxx"

SpaceStoneMonster::SpaceStoneMonster():
HierarchyEntity(
    GameDisplay::make_display()->get_geometries()->SPHERE(),
    GameDisplay::make_display()->get_loaded_shaders()->TEXTURED(),
    GameDisplay::get_loaded_textures()->SPACE_STONE_MONSTER_BODY()
)
{
    set_terrained(1);
    set_collision_width(10.0f);
    set_collision_height(12.0f);
    set_collision_depth(4.0f);
    
    Geometry *cylinder = GameDisplay::make_display()->get_geometries()->CYLINDER();
    Geometry *sphere = GameDisplay::make_display()->get_geometries()->SPHERE();
    Shader *procedural = GameDisplay::make_display()->get_loaded_shaders()->PROCEDURAL();
    Shader *textured = GameDisplay::make_display()->get_loaded_shaders()->TEXTURED();
    set_scale(glm::vec3(3.0f, 3.0f, 3.0f));
    Texture *body_tx = GameDisplay::get_loaded_textures()->SPACE_STONE_MONSTER_BODY();

    head = new HierarchyEntity(sphere, textured,
     GameDisplay::get_loaded_textures()->SPACE_STONE_MONSTER_FACE());
    head->set_translate(glm::vec3(0.0f, 0.7f, 0.0f));
    head->set_orientation(glm::angleAxis(glm::pi<float>() * 1.5f , glm::vec3(0.0f, 1.0f, 0.0f)));
    add_child_node(head);

    bottom = new HierarchyEntity(sphere, textured, body_tx);
    bottom->set_translate(glm::vec3(0.0f, -0.7f, 0.0f));
    add_child_node(bottom);

    for (uint8_t i = 0; i < 2; ++i)
    {
        shoulders[i] = new HierarchyEntity(sphere, textured, body_tx);
        shoulders[i]->set_translate(glm::vec3(-0.5 + i, 0.0f, 0.0f));
        add_child_node(shoulders[i]);
        float x_trans = -1.0f + i * 2.0f;
        arms[i] = new HierarchyEntity(cylinder, textured, body_tx);
        arms[i]->set_orientation(glm::angleAxis(glm::pi<float>() * 0.5f, glm::vec3(0.0f, 0.0f, 1.0f)));
        arms[i]->set_translate(glm::vec3(x_trans, 0.0f, 0.0f));
        arms[i]->set_scale(glm::vec3(0.2f, 1.0f, 0.2f));
        shoulders[i]->add_child_node(arms[i]);
        hands[i] = new HierarchyEntity(sphere, textured, body_tx);
        hands[i]->set_translate(glm::vec3(0.0f, 0.5 - i, 0.0f));
        hands[i]->set_scale(glm::vec3(1.0f, 0.2f, 1.0f));
        arms[i]->add_child_node(hands[i]);

        legs[i] = new HierarchyEntity(cylinder, textured, body_tx);
        bottom->add_child_node(legs[i]);
        legs[i]->set_translate(glm::vec3(-0.5f + i, -0.5f, 0.0f));
        legs[i]->set_scale(glm::vec3(0.2f, 2.0f, 0.2f));

        feet[i] = new HierarchyEntity(sphere, textured, body_tx);
        feet[i]->set_translate(glm::vec3(0.0f, -0.5f, 0.0f));
        feet[i]->set_scale(glm::vec3(2.0f, 0.2f, 2.0f));
        legs[i]->set_orbit(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.5f, 0.0f)));
        legs[i]->add_child_node(feet[i]);
    }

    set_entity_team(ENEMY);
    health = 150.0f;
}


void SpaceStoneMonster::update()
{
    if (health <= 0)
    {
        Supply *s = new Supply(STONE, 10.0f, 10.0f, GameDisplay::make_display()->get_current_game_world()->get_player());
        s->set_translate(get_position());
        GameDisplay::make_display()->get_current_game_world()->add_entity(s);
        remove();
        SpaceStoneMonster *ss = new SpaceStoneMonster;
        glm::vec2 rand_pos = GameDisplay::make_display()->get_current_game_world()->random_position();
        ss->set_translate(glm::vec3(rand_pos[0], 0.0f, rand_pos[1]));
        GameDisplay::make_display()->get_current_game_world()->add_entity(ss);
        SphereExplosion *e = new SphereExplosion;
        e->set_translate(get_position());
        GameDisplay::make_display()->get_current_game_world()->add_entity(e);

    }
    dance();
    HierarchyEntity::update();
}

void SpaceStoneMonster::handle_terrain_collision(const float &y, const float &gravity)
{
    if (y >= get_position()[1] - get_scale()[1] * 2.8f)
    {
        glm::vec3 position = get_position();
        set_translate(glm::vec3(position[0], y + get_scale()[1] * 2.8f, position[2]));
        set_translate_speed(glm::vec3(0.0f, -get_translate_speed()[1], 0.0f));
    }
    HierarchyEntity::handle_terrain_collision(y, gravity);
}

void SpaceStoneMonster::dance()
{
    last_time = glfwGetTime();

    for (uint8_t i = 0; i < 2; ++i) // You could say it's running :)
    {
        float angle = -(float)glm::cos(last_time * 5.0f);
        if (angle > glm::pi<float>() * 0.5f && angle < glm::pi<float>()) angle *= -1;
        shoulders[i]->set_orientation(glm::angleAxis( angle, glm::vec3(0.0f, 1.0f, 0.0f)));
        legs[i]->set_orientation(glm::angleAxis(!i ? angle : -angle, glm::vec3(1.0f, 0.0f, 0.0f)));
    }

}


void SpaceStoneMonster::handle_collision(Entity *e)
{
    if (e->get_entity_team() != get_entity_team() && e->get_entity_team() != NEUTRAL)
    {
        e->take_damage(70.0f);
    }
}


void SpaceStoneMonster::handle_other(Entity *e)
{
    if (e->get_entity_team() == ALLY)
    {
        if (glm::length(get_position() - e->get_position()) < 500.0f)
        translate(-glm::normalize(get_position() - e->get_position()));
    }
}