#include "SpaceSnail.hxx"
#include "Tank.hxx"
#include "../../World/GameWorld.hh"
#include "Supply.hxx"

SpaceSnail::SpaceSnail():
HierarchyEntity(
    GameDisplay::get_geometries()->CYLINDER(),
    GameDisplay::get_loaded_shaders()->TEXTURED(),
    GameDisplay::get_loaded_textures()->SPACE_SNAIL_BODY()
)
{
    set_terrained(1);
    set_orientation(glm::angleAxis(glm::pi<float>() * 0.5f, glm::vec3(0.0f, 0.0f, 1.0f)));
    set_scale(glm::vec3(5.0f, 10.0f, 5.0f));

    set_collision_width(12.0f);
    set_collision_height(12.0f);
    set_collision_depth(5.0f);

    Geometry *cylinder = GameDisplay::make_display()->get_geometries()->CYLINDER();
    Geometry *sphere = GameDisplay::make_display()->get_geometries()->SPHERE();
    Shader *procedural = GameDisplay::make_display()->get_loaded_shaders()->PROCEDURAL();
    Shader *textured = GameDisplay::get_loaded_shaders()->TEXTURED();
    Texture *body = GameDisplay::get_loaded_textures()->SPACE_SNAIL_BODY();
    Texture *shell_tx = GameDisplay::get_loaded_textures()->SPACE_SNAIL_SHELL();

    head = new HierarchyEntity(sphere, textured,
     GameDisplay::get_loaded_textures()->SPACE_SNAIL_FACE());
    head->set_translate(glm::vec3(0.0f, -0.6f, 0.0f));
    head->set_scale(glm::vec3(1.0f, 0.333, 1.0f));
    add_child_node(head);

    for (uint8_t i = 0; i < 2; ++i)
    {
        anthenas[i] = new HierarchyEntity(cylinder, textured, body);
        head->add_child_node(anthenas[i]);
        anthenas[i]->set_translate(glm::vec3(1.0f, 0.0f, -0.5f + i));
        anthenas[i]->set_orientation(glm::angleAxis(-glm::pi<float>() * 0.5f, glm::vec3(0.0f, 0.0f, 1.0f)));
        anthenas[i]->set_scale(glm::vec3(0.1f, 2.0f, 0.1f));

        anthena_tips[i] = new HierarchyEntity(sphere, textured, body);
        anthenas[i]->add_child_node(anthena_tips[i]);

        anthena_tips[i]->set_scale(glm::vec3(3.0f, 0.15f, 3.0f));
        anthena_tips[i]->set_translate(glm::vec3(0.0f, 0.5f, 0.0f));
    }
    shell = new HierarchyEntity(sphere, GameDisplay::get_loaded_shaders()->METAL(), shell_tx);
    add_child_node(shell);
    shell->set_translate(glm::vec3(0.75f, 0.0f, 0.0f));
    shell->set_scale(glm::vec3(2.0f, 0.8f, 2.0f));

    set_entity_team(ENEMY);
    mvmt = glm::vec3(1.0f, 0.0f, 0.0f);

}


void SpaceSnail::update()
{
    if (glfwGetTime() - last_time >= 5.0f)
    {
        mvmt *= -1.0f;
        last_time = glfwGetTime();
        rotate(glm::angleAxis(glm::pi<float>() * mvmt[0], glm::vec3(1.0f, 0.0f, 0.0f)));
    }
    translate(mvmt);
    if (health <= 0.0f)
    {
        remove();
        Supply *s = new Supply(SHELL, 50.0f, 10.0f, GameDisplay::make_display()->get_current_game_world()->get_player());
        s->set_translate(this->get_position());
        GameDisplay::make_display()->get_current_game_world()->add_entity(s);
    }
    HierarchyEntity::update();
}

void SpaceSnail::handle_terrain_collision(const float &y, const float &gravity)
{
    if (y >= get_position()[1] - get_scale()[0] - 0.2f)
    {
        glm::vec3 position = get_position();
        set_translate(glm::vec3(position[0], y + get_scale()[0] * 0.5f + 0.2f, position[2]));
    }
    HierarchyEntity::handle_terrain_collision(y, gravity);
}
