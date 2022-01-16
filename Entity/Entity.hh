#ifndef _ENTITY_HH_
#define _ENTITY_HH_
#include "../includes.hxx"
class Shader;
class Texture;
#include "Geometries/Geometries.hxx"
#include "../Shader/LoadedShaders.hxx"
#include "../Display/GameDisplay.hh"
#include "../Texture/LoadedTextures.hxx"

enum EntityTeam
{
    ALLY, ENEMY, NEUTRAL
};

/// <h2> Author: Kia Kalani </h2>
/// <strong> Student ID: 101145220 </strong>
/// <summary>
/// <code>Entity</code> class is the base class
/// for other entities that would be created within
/// this project. It contains basic transformations
/// of an object, the <code>Shader</code> used on it,
/// the <code>Geometry</code> of the shape, and the 
/// <code>Texture</code> corresponding to the object.
/// </summary>
/// <strong> Last Revised: Thursday, November 18th, 2021 </strong>
class Entity
{
    private:
    glm::vec3 position;
    glm::vec3 obj_scale;
    glm::quat orientation;
    glm::mat4 orbit;
    glm::mat4 parent;
    glm::vec3 trans_speed;
    glm::vec3 rot_speed;
    glm::vec4 uni_color;

    float collision_width, collision_height, collision_depth;
    
    bool removed = false;
    bool terrained;
    uint32_t count_dups;
    bool transparent;

    EntityTeam team;

    protected:
    Shader *shader;
    Geometry *shape;
    Texture *texture;
    Entity *colliding_objects;


    void set_shader(const Shader*&);
    void set_texture(const Texture*&);
    void set_geometry(const Geometry*&);

    // Calling this would add the attributes and other components that are necessary
    // to be sent to the shader.
    void setup_render_elems(const glm::mat4&, const glm::mat4&, const glm::mat4&) const;

    // This function draws the components that were sent to the shader.
    void setup_render_draw() const;

    // For instanced drawing.
    void set_count_duplicates(const uint32_t&);
    float health;

    public:
    Entity(Geometry*, Shader*, Texture* = (Texture*)0);
    
    glm::mat4 get_orbit() const;
    glm::vec3 get_position() const;
    glm::vec3 get_scale() const;
    glm::quat get_orientation() const;

    void translate(const glm::vec3&);
    void rotate(const glm::quat&);
    void scale(const glm::vec3&);

    void set_translate(const glm::vec3&);
    void set_orientation(const glm::quat&);
    void set_scale(const glm::vec3&);
    void set_orbit(const glm::mat4&);
    void set_parent(const glm::mat4&);
    void set_uni_color(const glm::vec4&);
    
    // For simple collision detection. 
    void set_collision_width(const float&);
    void set_collision_height(const float&);
    void set_collision_depth(const float&);

    // Render having the view, projection, and the 2D projection matrices
    virtual void render(const glm::mat4&, const glm::mat4&, const glm::mat4& = glm::mat4(1.0f)) const;
    virtual void update();
    
    // Used for removing an element from the game world.
    void remove();
    bool is_removed() const;
    bool is_transparent() const;
    void set_transparent(const bool&);
    bool is_terrained() const;
    void set_terrained(const bool&);
    // handles terrain collision with the entity
    virtual void handle_terrain_collision(const float&, const float&);
    glm::mat4 calculate_world() const;

    void set_translate_speed(const glm::vec3&);
    const glm::vec3 &get_translate_speed();

    virtual float get_collision_radius() const;

    bool collides(const Entity*&) const;

    virtual void handle_collision(Entity*);

    void take_damage(const float&);
    float get_health() const;

    void set_entity_team(const EntityTeam&);
    EntityTeam get_entity_team() const;

    virtual void handle_other(Entity*);


    void set_texture(Texture*);
};


#endif