#ifndef _BULLET_HXX_
#define _BULLET_HXX_
#include "../../../Entity/Entity.hh"
class Bullet: public Entity 
{
    private:
    // would get destroyed after those many seconds
    float lifespan;
    float creation_time;

    glm::vec3 forward;
    float bullet_speed;
    Entity *owner;

    float power;
    
    public:
    Bullet(const float&, const glm::vec3&, const float& = 10.0f, Entity* = (Entity*)0);

    void update();
    void set_power(const float&);

    float get_collision_radius() const; 
    void handle_terrain_collision(const float&, const float&);
    void handle_collision(Entity*);
};
#endif