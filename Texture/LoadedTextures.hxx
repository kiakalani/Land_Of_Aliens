#ifndef _LOADED_TEXTURES_HXX_
#define _LOADED_TEXTURES_HXX_


#define COUNT_INSTRUCTIONS 9
#include "Texture.hh"
#include <stdint.h>
class LoadedTextures
{
    private:
    Texture *tree_top;
    Texture *tree_body;

    Texture *tank_body;
    Texture *tank_tire;
    Texture *tank_window;

    Texture *dragon_head;
    Texture *dragon_body;

    Texture *space_stone_monster_face;
    Texture *space_stone_monster_body;

    Texture *space_snail_face;
    Texture *space_snail_body;
    Texture *space_snail_shell;

    Texture *terrain;

    Texture *space_jet_head;
    Texture *space_jet_body;

    Texture *bullet;

    Texture *star_face1;
    Texture *star_face2;
    Texture *star_body1;
    Texture *star_body2;

    Texture *gas_station;

    Texture *leader_face;
    Texture *leader_body;
    Texture *leader_crown;

    Texture *label;
    Texture *save;

    Texture *instructions[COUNT_INSTRUCTIONS];
    
    Texture *health_ic, *health_b, *fuel_ic, *fuel_b;
    Texture *gold_ic, *wood_ic, *dragon_ic, *stone_ic, *star_ic, *bullet_ic;
    public:
    LoadedTextures();
    ~LoadedTextures();

    Texture *HEALTH_IC() const;
    Texture *HEALTH_B() const;
    Texture *FUEL_IC() const;
    Texture *FUEL_B() const;
    Texture *GOLD_IC() const;
    Texture *WOOD_IC() const;
    Texture *DRAGON_IC() const;
    Texture *STONE_IC() const;
    Texture *STAR_IC() const;
    Texture *BULLET_IC() const;

    Texture *TREE_TOP() const;
    Texture *TREE_BODY() const;

    Texture *TANK_BODY() const;
    Texture *TANK_TIRE() const;
    Texture *TANK_WINDOW() const;
    
    Texture *DRAGON_HEAD() const;
    Texture *DRAGON_BODY() const;

    Texture *SPACE_STONE_MONSTER_FACE() const;
    Texture *SPACE_STONE_MONSTER_BODY() const;

    Texture *SPACE_SNAIL_FACE() const;
    Texture *SPACE_SNAIL_BODY() const;
    Texture *SPACE_SNAIL_SHELL() const;

    Texture *TERRAIN() const;

    Texture *SPACE_JET_HEAD() const;
    Texture *SPACE_JET_BODY() const;

    Texture *BULLET() const;

    Texture *STAR_FACE1() const;
    Texture *STAR_FACE2() const;
    Texture *STAR_BODY1() const;
    Texture *STAR_BODY2() const;

    Texture *GAS_STATION() const;

    Texture *LEADER_FACE() const;
    Texture *LEADER_CROWN() const;
    Texture *LEADER_BODY() const;
    
    Texture *LABEL() const;
    Texture *SAVE() const;
    
    Texture *INSTRUCTIONS(uint8_t) const;
};
#endif
