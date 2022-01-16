#ifndef _GAME_PAGE_HXX_
#define _GAME_PAGE_HXX_
#include "GameWorld.hh"
#include <stdint.h>
class Label;
class Entity;
class ProgressBar;
class Tank;
class GasStation;
class SupremeLeader;
class Save;
class GamePage: public GameWorld
{
    private: // Todo: Update labels and
    // progress bars from the tank entity
    Label *gold;
    Label *wood;
    Label *dragon_skin;
    Label *stone;
    Label *shell;
    Label *stars;
    Label *bullet;
    void setup_labels();
    
    ProgressBar *health;
    ProgressBar *fuel;

    Entity *gold_ic;
    Entity *wood_ic;
    Entity *dragon_ic;
    Entity *stone_ic;
    Entity *shell_ic;
    Entity *health_ic;
    Entity *fuel_ic;
    Entity *star_ic;
    Entity *bullet_ic;
    Entity *rain_fire_efct;

    GasStation *gas_station;

    Entity *low_health_disp;

    Texture *cp_disp;

    SupremeLeader *leader;
    Save *save;
    void setup_icons_and_bars();


    static void on_key_pressed(int, void*);
    static void on_key_released(int, void*);
    uint8_t count_entities;


    void handle_game_over();
    public:
    GamePage(Tank* = NULL);
    void set_event_handlers();

    void update();

    void update_labels();


    void generate_stone_monsters();
    void generate_enemy_stars();
    void generate_gas_stations();
    void generate_space_ships();
    void generate_space_dragons();
    void generate_space_snails();
    void create_supreme_leader();
    void generate_trees();

    float rand_float(float);
    void generate();

    void render(Camera*);

    
};
#endif
