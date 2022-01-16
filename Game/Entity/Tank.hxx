#ifndef _TANK_HXX_
#define _TANK_HXX_
#include "../../Entity/HierarchyEntity.hh"
class Tank: public HierarchyEntity
{
   
    private:
    HierarchyEntity *wheels[8];
    HierarchyEntity *gun_pipe;
    HierarchyEntity *window;
    HierarchyEntity *anthena;
    HierarchyEntity *anthena_tip;
    HierarchyEntity *door;
    HierarchyEntity *door_tip;
    // Speeds for making events smooth
    float up_rot;
    float forward_spd;
    float rotation_spd;

    float bullet_dmg;
    float max_health;

    float max_fuel;
    float fuel;

    uint16_t count_bullets;
    uint16_t count_d_skins;
    uint16_t count_gold;
    uint16_t count_wood;
    uint16_t count_stone;
    uint16_t count_stars;


    float bullet_power;

    bool boosting;
    

    public:
    Tank();
    void update();
    void handle_terrain_collision(const float &, const float&);

    void rotate_gun_pipe(const float&);
    void shoot();
    void handle_collision(Entity*);

    void set_rotation_spd(const float&);
    void set_forward_spd(const float&);

    float get_fuel_percent() const;
    float get_health_percent() const;

    uint16_t get_count_bullets() const;
    uint16_t get_count_d_skins() const;
    uint16_t get_count_gold() const;
    uint16_t get_count_wood() const;
    uint16_t get_count_stone() const;
    uint16_t get_count_stars() const;
    // Setters
    void set_count_bullets(const uint16_t&);
    void set_count_d_skins(const uint16_t&);
    void set_count_gold(const uint16_t&);
    void set_count_wood(const uint16_t&);
    void set_count_stone(const uint16_t&);
    void set_count_stars(const uint16_t&);

    void set_max_health(const float&);
    void set_health(const float&);
    void set_bullet_damage(const float&);
    void set_max_fuel(const float&);
    void set_fuel(const float&);

    // Functionalites that are used by key invokings
    void hire_rebel();
    void use_rebel();


    void heal(const float&);
    void fill_gas(const float&);

    void boost();
    void stop_boosting();

    float get_fuel() const;
    float get_max_fuel() const;

    float get_health() const;
    float get_max_health() const;

    float get_bullet_dmg() const;

    void create_bullet();

    void upgrade_bullet();
    void upgrade_fuel();
    void upgrade_health();
};

#endif