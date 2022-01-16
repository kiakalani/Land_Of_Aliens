#ifndef _SUPPLY_HXX_
#define _SUPPLY_HXX_
#include "../../Entity/Entity.hh"
class Tank;
enum SupplyType
{
    GOLD,
    FUEL,
    WOOD,
    DRAGON_SKIN,
    STONE,
    SHELL
};

class Supply: public Entity
{
    private:
    // How many to add to resources
    float value;
    // type of resource
    SupplyType type;

    // for removing if player does not interact with it
    float appearance_time;
    float longevity;
    // Player
    Entity *consumer;

    // Particles' positions
    glm::vec3 *particles;
    uint32_t count_particles;

    // Arrays containing the random angles
    float *x_multiples;
    float *y_multiples;
    float *z_multiples;

    // Count of all particles
    uint32_t count_multiples;

    public:
    Supply(SupplyType = GOLD, const float& = 1.0f, const float& = 1.0f, Entity *consumer = NULL);
    ~Supply();
    SupplyType get_type() const;

    void render(const glm::mat4&, const glm::mat4&, const glm::mat4&) const;

    void update();

    void handle_collision(Entity*);
    void handle_terrain_collision(const float&, const float&);

};
#endif
