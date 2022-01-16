#ifndef _SPHERE_EXPLOSION_HXX_
#define _SPHERE_EXPLOSION_HXX_
#include "../Entity.hh"
/// <h2> Author: Kia Kalani </h2>
/// <strong> Student ID: 101145220 </strong>
/// <summary>
/// <code>SphereExplosion</code> class is used for explosion
/// particle effect for the stone monsters
/// </summary>
/// <strong> Last Revised: Friday, December 17th, 2021 </strong>
class SphereExplosion: public Entity
{
    private:
    // Sorry for bad naming:
    float *explosion_angles;// explosion_angles = x angles
    float *expx;// expx =  y angles
    float *expy;// expy = z angles
    uint32_t count_explosion_angles;

    float appearance;

    public:
    SphereExplosion();
    ~SphereExplosion();

    void render(const glm::mat4&, const glm::mat4&, const glm::mat4&) const;

    void update();
};
#endif
