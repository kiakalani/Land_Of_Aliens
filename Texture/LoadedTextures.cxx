#include "LoadedTextures.hxx"
#include "../World/GameWorld.hh"
#include <stdio.h>
LoadedTextures::LoadedTextures()
{
    tree_top = new Texture((char*)TEXTURE_PATH"/Game/Entity/Tree/top.jpg");
    tree_body = new Texture((char*)TEXTURE_PATH"/Game/Entity/Tree/body.jpg");

    tank_body = new Texture((char*)TEXTURE_PATH"/Game/Entity/Tank/body.jpg");
    tank_tire = new Texture((char*)TEXTURE_PATH"/Game/Entity/Tank/tire.jpg");
    tank_window = new Texture((char*)TEXTURE_PATH"/Game/Entity/Tank/window.jpg");
    
    dragon_head = new Texture((char*)TEXTURE_PATH"/Game/Entity/SpaceDragon/face.jpg");
    dragon_body = new Texture((char*)TEXTURE_PATH"/Game/Entity/SpaceDragon/body.jpg");

    space_stone_monster_face = new Texture((char*)TEXTURE_PATH"/Game/Entity/SpaceStoneMonster/face.jpg");
    space_stone_monster_body = new Texture((char*)TEXTURE_PATH"/Game/Entity/SpaceStoneMonster/body.jpg");

    space_snail_face = new Texture((char*)TEXTURE_PATH"/Game/Entity/SpaceSnail/face.jpg");
    space_snail_body = new Texture((char*)TEXTURE_PATH"/Game/Entity/SpaceSnail/body.jpg");
    space_snail_shell = new Texture((char*)TEXTURE_PATH"/Game/Entity/SpaceSnail/shell.jpg");

    terrain = new Texture((char*)TEXTURE_PATH"/Entity/rocky.png");

    space_jet_head = new Texture((char*)TEXTURE_PATH"/Game/Entity/SpaceJet/head.jpg");
    space_jet_body = new Texture((char*)TEXTURE_PATH"/Game/Entity/SpaceJet/body.jpg");

    bullet = new Texture((char*)TEXTURE_PATH"/Game/Entity/Weapons/Bullet.jpg");

    star_face1 = new Texture((char*)TEXTURE_PATH"/Game/Entity/Star/face1.jpg");
    star_face2 = new Texture((char*)TEXTURE_PATH"/Game/Entity/Star/face2.jpg");
    star_body1 = new Texture((char*)TEXTURE_PATH"/Game/Entity/Star/body1.jpg");
    star_body2 = new Texture((char*)TEXTURE_PATH"/Game/Entity/Star/body2.jpg");

    gas_station = new Texture((char*)TEXTURE_PATH"/Game/Entity/GasStation/body.jpg");

    leader_face = new Texture((char*)TEXTURE_PATH"/Game/Entity/SupremeLeader/face.jpg");
    leader_body = new Texture((char*)TEXTURE_PATH"/Game/Entity/SupremeLeader/body.jpg");
    leader_crown = new Texture((char*)TEXTURE_PATH"/Game/Entity/SupremeLeader/crown.jpg");

    label = new Texture((char*)TEXTURE_PATH"/alphabets.png");

    save = new Texture((char*)TEXTURE_PATH"/Game/Entity/Save/save.jpg");


    char file_path[200];
    for (uint8_t i = 0; i < COUNT_INSTRUCTIONS; ++i)
    {
        sprintf(file_path, TEXTURE_PATH"/Instructions/%u.png", i + 1);
        instructions[i] = new Texture(file_path);
    }

    health_ic = new Texture((char*)TEXTURE_PATH"/Entity/gameIcons/health.jpg");
    health_b = new Texture((char*)TEXTURE_PATH"/Entity/gameIcons/health_bar.jpg");
    fuel_ic = new Texture((char*)TEXTURE_PATH"/Entity/gameIcons/fuel.jpg");
    fuel_b = new Texture((char*)TEXTURE_PATH"/Entity/gameIcons/fuel_bar.jpg");
    gold_ic = new Texture((char*)TEXTURE_PATH"/Entity/gameIcons/gold.jpg");
    wood_ic = new Texture((char*)TEXTURE_PATH"/Entity/gameIcons/wood.jpg");
    dragon_ic = new Texture((char*)TEXTURE_PATH"/Entity/gameIcons/dragon_skin.jpg");
    stone_ic = new Texture((char*)TEXTURE_PATH"/Entity/gameIcons/stone.jpg");
    star_ic = new Texture((char*)TEXTURE_PATH"/Entity/gameIcons/star.jpg");
    bullet_ic = new Texture((char*)TEXTURE_PATH"/Entity/gameIcons/bullet.jpg");
}

LoadedTextures::~LoadedTextures()
{
    delete tree_body;
    delete tree_top;

    delete tank_body;
    delete tank_tire;
    delete tank_window;

    delete dragon_head;
    delete dragon_body;

    delete space_stone_monster_face;
    delete space_stone_monster_body;

    delete space_snail_face;
    delete space_snail_body;
    delete space_snail_shell;

    delete terrain;

    delete space_jet_head;
    delete space_jet_body;

    delete bullet;

    delete star_face1;
    delete star_face2;
    delete star_body1;
    delete star_body2;

    delete gas_station;

    delete leader_body;
    delete leader_crown;
    delete leader_face;

    delete label;
    delete save;

    for (uint8_t i = 0; i < COUNT_INSTRUCTIONS; ++i) delete instructions[i];

    delete health_ic;
    delete health_b;
    delete fuel_ic;
    delete fuel_b;
    delete gold_ic;
    delete wood_ic;
    delete dragon_ic;
    delete stone_ic;
    delete star_ic;
    delete bullet_ic;
}

Texture *LoadedTextures::TREE_TOP() const
{
    return tree_top;
}
Texture *LoadedTextures::TREE_BODY() const
{
    return tree_body;
}

Texture *LoadedTextures::TANK_BODY() const
{
    return tank_body;
}
Texture *LoadedTextures::TANK_TIRE() const
{
    return tank_tire;
}
Texture *LoadedTextures::TANK_WINDOW() const
{
    return tank_window;
}

Texture *LoadedTextures::DRAGON_HEAD() const
{
    return dragon_head;
}
Texture *LoadedTextures::DRAGON_BODY() const
{
    return dragon_body;
}

Texture *LoadedTextures::SPACE_STONE_MONSTER_FACE() const
{
    return space_stone_monster_face;
}
Texture *LoadedTextures::SPACE_STONE_MONSTER_BODY() const
{
    return space_stone_monster_body;
}

Texture *LoadedTextures::SPACE_SNAIL_FACE() const
{
    return space_snail_face;
}
Texture *LoadedTextures::SPACE_SNAIL_BODY() const
{
    return space_snail_body;
}
Texture *LoadedTextures::SPACE_SNAIL_SHELL() const
{
    return space_snail_shell;
}

Texture *LoadedTextures::TERRAIN() const
{
    return terrain;
}

Texture *LoadedTextures::SPACE_JET_HEAD() const
{
    return space_jet_head;
}

Texture *LoadedTextures::SPACE_JET_BODY() const
{
    return space_jet_body;
}

Texture *LoadedTextures::BULLET() const
{
    return bullet;
}

Texture *LoadedTextures::STAR_FACE1() const
{
    return star_face1;
}
Texture *LoadedTextures::STAR_FACE2() const
{
    return star_face2;
}
Texture *LoadedTextures::STAR_BODY1() const
{
    return star_body1;
}
Texture *LoadedTextures::STAR_BODY2() const
{
    return star_body2;
}

Texture *LoadedTextures::GAS_STATION() const
{
    return gas_station;
}

Texture *LoadedTextures::LEADER_BODY() const
{
    return leader_body;
}

Texture *LoadedTextures::LEADER_FACE() const
{
    return leader_face;
}

Texture *LoadedTextures::LEADER_CROWN() const
{
    return leader_crown;
}

Texture *LoadedTextures::LABEL() const
{
    return label;
}

Texture *LoadedTextures::SAVE() const
{
    return save;
}


Texture *LoadedTextures::INSTRUCTIONS(uint8_t i) const
{
    return instructions[i];
}

Texture *LoadedTextures::HEALTH_IC() const
{
    return health_ic;
}
Texture *LoadedTextures::HEALTH_B() const
{
    return health_b;
}
Texture *LoadedTextures::FUEL_IC() const
{
    return fuel_ic;
}
Texture *LoadedTextures::FUEL_B() const
{
    return fuel_b;
}
Texture *LoadedTextures::GOLD_IC() const
{
    return gold_ic;
}
Texture *LoadedTextures::WOOD_IC() const
{
    return wood_ic;
}
Texture *LoadedTextures::DRAGON_IC() const
{
    return dragon_ic;
}
Texture *LoadedTextures::STONE_IC() const
{
    return stone_ic;
}
Texture *LoadedTextures::STAR_IC() const
{
    return star_ic;
}
Texture *LoadedTextures::BULLET_IC() const
{
    return bullet_ic;
}
