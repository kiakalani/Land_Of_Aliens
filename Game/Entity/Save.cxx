#include "Save.hxx"
#include "Tank.hxx"
#include "../../World/GameWorld.hh"
#include <stdio.h>


Save::Save(): Entity(GameDisplay::get_geometries()->CYLINDER(), GameDisplay::get_loaded_shaders()->TEXTURED(),
GameDisplay::get_loaded_textures()->SAVE())
{
    set_terrained(1);
    set_scale(glm::vec3(10.0f, 15.0f, 10.0f));
}



void Save::handle_terrain_collision(const float &y, const float &gravity)
{
    if (y >= get_position()[1] - get_scale()[1] * 0.5f)
    {
        glm::vec3 position = get_position();
        set_translate_speed(glm::vec3(0.0f, -get_translate_speed()[1], 0.0f));
        set_translate(glm::vec3(position[0], y + get_scale()[1] * 0.5f, position[2]));
    }
}


void Save::save_game()
{
    Tank *player = GameDisplay::make_display()->get_current_game_world()->get_player();
    if (player->get_count_wood() >= 50)
    {
        player->set_count_wood(player->get_count_wood() - 50);
        set_translate(glm::vec3(0.0f, 0.0f, 20.0f) + GameDisplay::make_display()->get_current_game_world()->get_player()->get_position());
        save_tank();
    }
}



void Save::save_tank()
{
    Tank *player = GameDisplay::make_display()->get_current_game_world()->get_player();
    float health = player->get_health();
    float max_health = player->get_max_health();
    float bullet_dmg = player->get_bullet_dmg();
    float max_fuel = player->get_max_fuel();
    float fuel = player->get_fuel();

    uint16_t count_bullets = player->get_count_bullets();
    uint16_t count_d_skins = player->get_count_d_skins();
    uint16_t count_gold = player->get_count_gold();
    uint16_t count_wood = player->get_count_wood();
    uint16_t count_stone = player->get_count_stone();
    uint16_t count_stars = player->get_count_stars();

    FILE *f = fopen(SAVE_FILE, "w");
    fwrite(&health, sizeof(float), 1, f);
    fwrite(&max_health, sizeof(float), 1, f);
    fwrite(&bullet_dmg, sizeof(float), 1, f);
    fwrite(&max_fuel, sizeof(float), 1, f);
    fwrite(&fuel, sizeof(float), 1, f);

    fwrite(&count_bullets, sizeof(uint16_t), 1, f);
    fwrite(&count_d_skins, sizeof(uint16_t), 1, f);
    fwrite(&count_gold, sizeof(uint16_t), 1, f);
    fwrite(&count_wood, sizeof(uint16_t), 1, f);
    fwrite(&count_stone, sizeof(uint16_t), 1, f);
    fwrite(&count_stars, sizeof(uint16_t), 1, f);

    fclose(f);
}


Tank *Save::load_game()
{
    Tank *t = new Tank;
    float health = 0;
    float max_health = 0;
    float bullet_dmg = 0;
    float max_fuel = 0;
    float fuel = 0;

    uint16_t count_bullets = 0;
    uint16_t count_d_skins = 0;
    uint16_t count_gold = 0;
    uint16_t count_wood = 0;
    uint16_t count_stone = 0;
    uint16_t count_stars = 0;

    FILE *f = fopen(SAVE_FILE, "r");
    fread(&health, sizeof(float), 1, f);
    fread(&max_health, sizeof(float), 1, f);
    fread(&bullet_dmg, sizeof(float), 1, f);
    fread(&max_fuel, sizeof(float), 1, f);
    fread(&fuel, sizeof(float), 1, f);

    fread(&count_bullets, sizeof(uint16_t), 1, f);
    fread(&count_d_skins, sizeof(uint16_t), 1, f);
    fread(&count_gold, sizeof(uint16_t), 1, f);
    fread(&count_wood, sizeof(uint16_t), 1, f);
    fread(&count_stone, sizeof(uint16_t), 1, f);
    fread(&count_stars, sizeof(uint16_t), 1, f);
    fclose(f);

    t->set_health(health);
    t->set_max_health(max_health);
    t->set_bullet_damage(bullet_dmg);
    t->set_max_fuel(max_fuel);
    t->set_fuel(fuel);

    t->set_count_bullets(count_bullets);
    t->set_count_d_skins(count_d_skins);
    t->set_count_gold(count_gold);
    t->set_count_wood(count_wood);
    t->set_count_stone(count_stone);
    t->set_count_stars(count_stars);

    return t;
}