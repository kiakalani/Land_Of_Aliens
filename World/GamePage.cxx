#include "GamePage.hxx"
#include "../Entity/Label.hh"
#include "../Entity/ProgressBar.hxx"
#include "../Game/Entity/Tank.hxx"
#include "../Camera/Camera.hh"
#include "../Entity/Entities/Terrain.hxx"
#include "Pause.hxx"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Game/Entity/Tree.hxx"
#include "../Game/Entity/SpaceStoneMonster.hxx"
#include "../Game/Entity/GasStation.hxx"
#include "../Game/Entity/SpaceDragon.hxx"
#include "../Game/Entity/Star.hxx"
#include "../Game/Entity/SpaceJet.hxx"
#include "../Game/Entity/SpaceSnail.hxx"
#include "../Game/Entity/SupremeLeader.hxx"
#include "../Game/Entity/Save.hxx"
#include "GameOver.hxx"
#include "../Entity/Entities/Atom.hxx"

GamePage::GamePage(Tank *t): GameWorld()
{
    
    setup_labels();
    setup_icons_and_bars();
    if (t) player = t;
    else 
    player = new Tank;
    GameDisplay::make_display()->reset_camera();
    GameDisplay::make_display()->get_camera()->follow_entity(player);
    terrain = new Terrain;
    add_entity(terrain);
    player->set_translate(terrain->get_position() + terrain->get_scale());
    add_entity(player);
    generate();

    rain_fire_efct = new Entity(GameDisplay::get_geometries()->QUAD(), GameDisplay::get_loaded_shaders()->RAIN_FIRE(), NULL);
    rain_fire_efct->set_scale(glm::vec3(50.0f, 50.0f, 50.0f));
    rain_fire_efct->set_transparent(1);
    add_entity(rain_fire_efct);

    cp_disp = new Texture;
    low_health_disp = new Entity(GameDisplay::get_geometries()->QUAD(), GameDisplay::get_loaded_shaders()->LOW_HEALTH(), cp_disp);

    low_health_disp->set_scale(glm::vec3(50.0f, 50.0f, 50.0f));
    
    
}

void GamePage::set_event_handlers()
{
    GameDisplay::make_display()->receive_pointer((void*)this);
    GameDisplay::make_display()->add_on_key_pressed(on_key_pressed);
    GameDisplay::make_display()->add_on_key_released(on_key_released);
}

void GamePage::generate()
{
    generate_stone_monsters();
    generate_enemy_stars();
    generate_gas_stations();
    generate_space_ships();
    generate_space_dragons();
    generate_space_snails();
    create_supreme_leader();
    generate_trees();
}

void GamePage::on_key_pressed(int k, void *ptrs)
{
    GamePage *g = (GamePage*)(((void**)ptrs)[0]);
    switch (k)
    {
        case GLFW_KEY_W:
            g->player->set_forward_spd(2.0f);
            break;
        case GLFW_KEY_S:
            g->player->set_forward_spd(-2.0f);
            break;
        case GLFW_KEY_A:
            g->player->set_rotation_spd(0.01f);
            break;
        case GLFW_KEY_D:
            g->player->set_rotation_spd(-0.01f);
            break;
        case GLFW_KEY_LEFT_SHIFT:
            g->player->boost();
            break;

    }
}

void GamePage::on_key_released(int k, void *ptrs)
{
    GamePage *g = (GamePage*)(((void**)ptrs)[0]);
    switch (k)
    {
        case GLFW_KEY_W:
            g->player->set_forward_spd(0.0f);
            break;
        case GLFW_KEY_S:
            g->player->set_forward_spd(-0.0f);
            break;
        case GLFW_KEY_A:
            g->player->set_rotation_spd(0.0f);
            break;
        case GLFW_KEY_D:
            g->player->set_rotation_spd(-0.0f);
            break;
        case GLFW_KEY_K:
            g->player->shoot();
            break;
        case GLFW_KEY_LEFT_SHIFT:
            g->player->stop_boosting();
            break;
        case GLFW_KEY_C:
            g->gas_station->answer_call();
            break;
        case GLFW_KEY_R:
            g->gas_station->refill_tank();
            break;
        case GLFW_KEY_Q:
            g->player->create_bullet();
            break;
        case GLFW_KEY_H:
            g->player->hire_rebel();
            break;
        case GLFW_KEY_U:
            g->player->use_rebel();
            break;
        case GLFW_KEY_Z:
        {
            if (!g->save)
            {
                g->save = new Save;
                g->add_entity(g->save);
            }
            g->save->save_game();
        }
            break;
        case GLFW_KEY_1:
            g->player->upgrade_health();
            break;
        case GLFW_KEY_2:
            g->player->upgrade_bullet();
            break;
        case GLFW_KEY_3:
            g->player->upgrade_fuel();
            break;

        case GLFW_KEY_ESCAPE:
            GameDisplay::make_display()->get_camera()->follow_entity(NULL);
            GameDisplay::make_display()->set_world(new Pause(((GamePage*)((void**)ptrs)[0])), 0);
            break;
    }
}


void GamePage::setup_labels()
{
    gold = new Label;
    gold->set_transparent(1);
    gold->set_text((char*)"0");
    gold->set_translate(glm::vec3(1.0f, -46.0f, 1.0f));
    gold->set_scale(glm::vec3(3.0f, 2.5f, 0.0f));
    gold->set_text_color(100, 50, 0);
    add_entity(gold);

    health = new ProgressBar(GameDisplay::get_loaded_textures()->HEALTH_B());
    health->set_translate(glm::vec3(-35.0f, -45.0f, 0.01f));
    health->set_scale(glm::vec3(7.0f, 3.0f, 1.0f));
    health->set_progress(100.0f);
    add_entity(health);

    fuel = new ProgressBar(GameDisplay::get_loaded_textures()->FUEL_B());
    fuel->set_translate(glm::vec3(-15.0f, -45.0f, 0.01f));
    fuel->set_scale(glm::vec3(7.0f, 3.0f, 1.0f));
    fuel->set_progress(100.0f);
    add_entity(fuel);

    wood = new Label;
    wood->set_text((char*)"0");
    wood->set_transparent(1);
    wood->set_translate(glm::vec3(13.0f, -46.0f, 1.0f));
    wood->set_scale(glm::vec3(3.0f, 2.5f, 0.0f));
    wood->set_text_color(100, 50, 0);
    add_entity(wood);

    dragon_skin = new Label;
    dragon_skin->set_text((char*)"0");
    dragon_skin->set_transparent(1);
    dragon_skin->set_translate(glm::vec3(24.0f, -46.0f, 1.0f));
    dragon_skin->set_scale(glm::vec3(3.0f, 2.5f, 0.0f));
    dragon_skin->set_text_color(100, 50, 0);
    add_entity(dragon_skin);

    stone = new Label;
    stone->set_text((char*)"0");
    stone->set_transparent(1);
    stone->set_translate(glm::vec3(35.0f, -46.0f, 0.0f));
    stone->set_scale(glm::vec3(3.0f, 2.5f, 0.0f));
    stone->set_text_color(100, 50, 0);
    add_entity(stone);

    stars = new Label;
    stars->set_text((char*)"0");
    stars->set_transparent(1);
    stars->set_translate(glm::vec3(45.0f, -41.0f, 0.0f));
    stars->set_scale(glm::vec3(3.0f, 2.5f, 0.0f));
    stars->set_text_color(100, 50, 0);
    add_entity(stars);

    bullet = new Label;
    bullet->set_text((char*)"0");
    bullet->set_transparent(1);
    bullet->set_translate(glm::vec3(45.0f, -46.0f, 0.0f));
    bullet->set_scale(glm::vec3(3.0f, 2.5f, 0.0f));
    bullet->set_text_color(100, 50, 0);
    add_entity(bullet);
}

void GamePage::setup_icons_and_bars()
{
    Geometry *quad = GameDisplay::get_geometries()->QUAD();
    Shader *tparent = GameDisplay::get_loaded_shaders()->WHITE_TPARENT();

    gold_ic = new Entity(quad, tparent, GameDisplay::get_loaded_textures()->GOLD_IC());
    gold_ic->set_translate(glm::vec3(-5.0f, -45.0f, 1.0f));
    gold_ic->set_scale(glm::vec3(3.0f, 3.0f, 0.01f));
    gold_ic->set_transparent(1);
    add_entity(gold_ic);

    health_ic = new Entity(quad, tparent, GameDisplay::get_loaded_textures()->HEALTH_IC());
    health_ic->set_translate(glm::vec3(-45.0f, -45.0f, 0.01f));
    health_ic->set_scale(glm::vec3(3.0f, 3.0f, 0.1f));
    health_ic->set_transparent(1);
    add_entity(health_ic);

    fuel_ic = new Entity(quad, tparent, GameDisplay::get_loaded_textures()->FUEL_IC());
    fuel_ic->set_translate(glm::vec3(-25.0f, -45.0f, 0.0f));
    fuel_ic->set_scale(glm::vec3(3.0f, 3.0f, 1.0f));
    fuel_ic->set_transparent(1);
    add_entity(fuel_ic);

    wood_ic = new Entity(quad, tparent, GameDisplay::get_loaded_textures()->WOOD_IC());
    wood_ic->set_translate(glm::vec3(7.0f, -45.0f, 0.0f));
    wood_ic->set_scale(glm::vec3(3.0f, 3.0f, 1.0f));
    wood_ic->set_transparent(1);
    add_entity(wood_ic);

    dragon_ic = new Entity(quad, tparent, GameDisplay::get_loaded_textures()->DRAGON_IC());
    dragon_ic->set_translate(glm::vec3(19.0f, -45.0f, 0.0f));
    dragon_ic->set_scale(glm::vec3(3.0f, 3.0f, 1.0f));
    dragon_ic->set_transparent(1);
    add_entity(dragon_ic);

    stone_ic = new Entity(quad, tparent, GameDisplay::get_loaded_textures()->STONE_IC());
    stone_ic->set_translate(glm::vec3(29.0f, -45.0f, 0.0f));
    stone_ic->set_scale(glm::vec3(3.0f, 3.0f, 1.0f));
    stone_ic->set_transparent(1);
    add_entity(stone_ic);

    star_ic = new Entity(quad, tparent, GameDisplay::get_loaded_textures()->STAR_IC());
    star_ic->set_translate(glm::vec3(40.0f, -40.0f, 0.0f));
    star_ic->set_scale(glm::vec3(3.0f, 3.0f, 1.0f));
    star_ic->set_transparent(1);
    add_entity(star_ic);

    bullet_ic = new Entity(quad, tparent, GameDisplay::get_loaded_textures()->BULLET_IC());
    bullet_ic->set_translate(glm::vec3(40, -45.0f, 0.0));
    bullet_ic->set_scale(glm::vec3(3.0f, 3.0f, 1.0f));
    bullet_ic->set_transparent(1);
    add_entity(bullet_ic);
}

void GamePage::update()
{
    GameWorld::update();
    fuel->set_progress(player->get_fuel_percent());
    health->set_progress(player->get_health_percent());
    update_labels();
    handle_game_over();
}


void GamePage::update_labels()
{
    char num[15];
    sprintf(num, "%u", player->get_count_gold());
    gold->set_text(num);

    sprintf(num, "%u", player->get_count_stars());
    stars->set_text(num);

    sprintf(num, "%u", player->get_count_d_skins());
    dragon_skin->set_text(num);

    sprintf(num, "%u", player->get_count_wood());
    wood->set_text(num);
    
    sprintf(num, "%u", player->get_count_stone());
    stone->set_text(num);

    sprintf(num, "%u", player->get_count_bullets());
    bullet->set_text(num);
}

float GamePage::rand_float(float ceiling)
{
    float rand_mult = (float)rand() / RAND_MAX;

    return rand_mult * ceiling;
}

void GamePage::generate_stone_monsters()
{
    for (uint8_t i = 0; i < 15; ++i)
    {
        SpaceStoneMonster *m = new SpaceStoneMonster;
        glm::vec2 rand_pos = random_position();
        m->set_translate(glm::vec3(rand_pos[0], 10.0f, rand_pos[1]));
        add_entity(m);
    }
}
void GamePage::generate_enemy_stars()
{
    for (uint8_t i = 0; i < 20; ++i)
    {
        Star *s = new Star(0);
        glm::vec2 r_pos = random_position();
        s->set_translate(glm::vec3(r_pos[0], 0.0f, r_pos[1]));
        add_entity(s);
    }
}
void GamePage::generate_gas_stations()
{
    gas_station = new GasStation;
    gas_station->set_translate(glm::vec3(80.0f, 10.0f, 80.0f));
    add_entity(gas_station);
}
void GamePage::generate_space_ships()
{
    for (uint8_t i = 0; i < 5; ++i)
    {
        SpaceJet *s = new SpaceJet;
        glm::vec2 r_pos = random_position();
        s->set_translate(glm::vec3(r_pos[0], 0.0f, r_pos[1]));
        add_entity(s);
    }
    SpaceJet *d = new SpaceJet;
    d->set_translate(glm::vec3(150.0f, 150.0f, 150.0f));
    add_entity(d);

}
void GamePage::generate_space_dragons()
{
    for (uint8_t i = 0; i < 10; ++i)
    {
        SpaceDragon *s = new SpaceDragon;
        glm::vec2 r_pos = random_position();
        s->set_translate(glm::vec3(r_pos[0], 0.0f, r_pos[1]));
        add_entity(s);
    }
    
}
void GamePage::generate_space_snails()
{
    for (uint8_t i = 0; i < 5; ++i)
    {
        SpaceSnail *s = new SpaceSnail;
        glm::vec2 r_pos = random_position();
        s->set_translate(glm::vec3(r_pos[0], 0.0f, r_pos[1]));
        add_entity(s);
    }
    
}
void GamePage::create_supreme_leader()
{
    leader = new SupremeLeader;
    // leader->set_translate(glm::vec3(500.0f, 10.0f, 500.0f));
    leader->set_translate(glm::vec3(terrain->max_x() - 100.0f, 0.0f, terrain->max_z() - 100.0f));
    add_entity(leader);

}
void GamePage::generate_trees()
{
    for (uint8_t i = 0; i < 30; ++i)
    {
        Tree *tree = new Tree;
        
        tree->set_translate(glm::vec3(rand_float(terrain->max_x()), 50.0f, rand_float(terrain->max_z())));
        
        add_entity(tree);
    }
}


void GamePage::handle_game_over()
{
    if (player->get_health() <= 0.0f || player->get_fuel() <= 0.0f)
    {
        GameDisplay::make_display()->set_world(new GameOver(0), 1);
    }
    else if (leader->get_health() <= 0.0f)
    {
        GameDisplay::make_display()->set_world(new GameOver(1), 1);
    }
}


void GamePage::render(Camera *c)
{

    if (player->get_health_percent() <= 30.0f || player->get_fuel_percent() <= 30.0f)
    {
        cp_disp->render_scene_to_texture();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    GameWorld::render(c);
    cp_disp->end_render_scene_to_texture();

    if (player->get_health_percent() <= 30.0f || player->get_fuel_percent() <= 30.0f)
    {

        low_health_disp->render(c->get_view_mat(), c->get_projection_mat(), c->get_2d_proj_mat());
    }
}