#ifndef _GAME_WORLD_HH_
#define _GAME_WORLD_HH_
#include "../includes.hxx"
#include "../Shader/LoadedShaders.hxx"
class Texture;
class Shader;
class Geometry;
class Camera;
class Terrain;
class Entity;
class Tank;

#define SHADER_PATH "../../Shaders"
#define TEXTURE_PATH "../../Textures"

/// <h2> Author: Kia Kalani </h2>
/// <strong> Student ID: 101145220 </strong>
/// <summary>
/// <code>GameWorld</code> class represents each
/// scene that would be shown to the player. This
/// can be either a menu, a scene of the game, or
/// the credits of the game.
/// </summary>
/// <strong> Last Revised: Thursday, November 18th, 2021 </strong>
class GameWorld
{
    private:
    const float gravity;
    // A stack type of data structure for the game entities.
    // On each updating, if the element is removed, it gets
    // deleted from the game world. It is basically runtime
    // add, remove, render, handle, and update on the game
    // entities.
    class EntityNode
    {
        public:
        EntityNode *next;
        Entity *entity;
    };
    EntityNode *head, *tail;
    protected:
    Terrain *terrain;
    Tank *player;
    public:
    GameWorld();
    virtual ~GameWorld();
    virtual void render(Camera*);
    virtual void update();
    // adding an entity to the game world.
    void add_entity(Entity*);
    Tank *get_player() const;

    virtual void set_event_handlers();

    glm::vec2 random_position() const;
// Todo
};

#endif