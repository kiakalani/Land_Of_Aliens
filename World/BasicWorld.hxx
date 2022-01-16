#ifndef _BASIC_WORLD_HXX_
#define _BASIC_WORLD_HXX_
#include "GameWorld.hh"
#include "../Entity/ProgressBar.hxx"
#include "../Entity/Label.hh"
#include "../Game/Entity/Tank.hxx"
#include "../Entity/Entities/Terrain.hxx"
// A class derived from GameWorld class for
// doing the assignments on.
class Star;
class Tree;
class GasStation;
class SpaceStoneMonster;
class SpaceSnail;
class SpaceJet;
class SpaceDragon;
class SupremeLeader;
class BasicWorld: public GameWorld
{
    public:
    // Mouse pressed event handler
    static void onMousePressed(int, void*);

    // Textures for text and progress bar
    Texture *text_table;
    Texture *progress_txtr;

    // Shaders for text and progress bar
    Shader *text_shader;
    Shader *progress_shader;
    Shader *proc_sh;

    // A quad instance
    Geometry *q_geom;
    Geometry *c_geom;

    Label *leftbtn;
    Label *rightbtn;
    Label *up_btn;
    Label *down_btn;

    Tank *tank;
    GasStation *leader;

    ProgressBar *progress;

    uint32_t count_up_clicks;
    static void onKeyPressed(int key, void *ptrs);
    static void onKeyReleased(int key, void *ptrs);
    public:
    BasicWorld();
    ~BasicWorld();
    virtual void update();
    void set_event_handlers();
};
#endif