#include "SupremeLeader.hxx"
#include "Tank.hxx"
#include "../../World/GameWorld.hh"
#include "Weapons/Bullet.hxx"
SupremeLeader::SupremeLeader(): HierarchyEntity(GameDisplay::make_display()->get_geometries()->CYLINDER(),
    (Shader*)GameDisplay::get_loaded_shaders()->METAL(),
     GameDisplay::get_loaded_textures()->LEADER_BODY())
{
    Texture *face = GameDisplay::get_loaded_textures()->LEADER_FACE();
    Texture *body_txt = GameDisplay::get_loaded_textures()->LEADER_BODY();
    Texture *crown_txt = GameDisplay::get_loaded_textures()->LEADER_CROWN();

    Geometry *sphere = GameDisplay::get_geometries()->SPHERE();
    Geometry *cylinder = GameDisplay::get_geometries()->CYLINDER();
    Shader *procedural = (Shader*)GameDisplay::get_loaded_shaders()->PROCEDURAL();
    Shader *textured = GameDisplay::get_loaded_shaders()->TEXTURED();
    set_terrained(1);
    set_scale(glm::vec3(4.0f, 9.0f, 4.0f));
    set_collision_width(4.0f);
    set_collision_height(13.5);
    set_collision_depth(4.0f);

    for (uint8_t i = 0; i < 2; ++i)
    {
        hands[i] = new HierarchyEntity(cylinder, textured, body_txt); 
        add_child_node(hands[i]);
        hands[i]->set_translate(glm::vec3(0.75f + (-1.5f * i), 0.30f, 0.0f));

        hands[i]->set_scale(glm::vec3(0.25f, 0.35f, 0.25f));
    }

    for (uint8_t i = 0; i < 3; ++i)
    {
        legs[i] = new HierarchyEntity(sphere, textured, body_txt);
        add_child_node(legs[i]);
        legs[i]->set_scale(glm::vec3(0.3f, 0.3f * 0.25, 0.3f));
        legs[i]->set_translate(glm::vec3(-0.5 + (i * 0.5), -0.55f, 0.0f));
    }

    head = new HierarchyEntity(sphere, textured, face);
    add_child_node(head);
    head->set_scale(glm::vec3(1.0f, 0.25f, 1.0f));

    head->set_translate(glm::vec3(0.0f, 0.60f, 0.0f));

    for (uint8_t i = 0; i < 8; ++i)
    {
        crown_body[i] = new HierarchyEntity(cylinder, textured, crown_txt);
        head->add_child_node(crown_body[i]);
        crown_body[i]->set_scale(glm::vec3(0.125, 1.0f, 0.125f));
        crown_body[i]->set_translate(glm::vec3(0.4f - ((i >> 1) * 0.25), 0.5f, (i % 2) - 0.25f));
    }

    for (uint8_t i = 0; i < 4; ++i)
    {
        crown_top[i] = new HierarchyEntity(sphere, textured, crown_txt);
        crown_body[i << 1]->add_child_node(crown_top[i]);

        crown_top[i]->set_scale(glm::vec3(2.0f, 0.125f, 10.0f));
        crown_top[i]->set_translate(glm::vec3(0.0f, 0.55f, 2.5f));
    }
    set_entity_team(ENEMY);
    health = 10000.0f;

}

void SupremeLeader::update()
{
    HierarchyEntity::update();
}

void SupremeLeader::handle_terrain_collision(const float &y, const float &gravity)
{
    if (y > get_position()[1] - get_scale()[1])
    {
        glm::vec3 position = get_position();
        set_translate(glm::vec3(position[0], y + get_scale()[1], position[2]));
        set_translate_speed(glm::vec3(0.0f, -get_translate_speed()[1], 0.0f));

    }
    
    HierarchyEntity::handle_terrain_collision(y, gravity);

}

void SupremeLeader::handle_collision(Entity *e)
{
    if (e->get_entity_team() == ALLY)
    {
        e->take_damage(500.0f);
    }
}


void SupremeLeader::handle_other(Entity *e)
{
    if (e->get_entity_team() == ALLY)
    {
        glm::vec3 diff = e->get_position() - get_position();
        if (glm::length(diff) <= 700.0f)
        {
            glm::vec3 normalized = glm::normalize(diff);
            float time = glfwGetTime();
            if (time - last_bullet >=   1.0f)
            {
                Bullet *b = new Bullet(50.0f, normalized, 15.0f, this);
                b->set_translate(get_position());
                GameDisplay::make_display()->get_current_game_world()->add_entity(b);
                last_bullet = time;
            }
            translate(8.0f * normalized);
        }
        
    }
}