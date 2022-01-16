#ifndef _ATOM_HXX_
#define _ATOM_HXX_
#include "../Entity.hh"
#include <stdint.h>
/// <h2> Author: Kia Kalani </h2>
/// <strong> Student ID: 101145220 </strong>
/// <summary>
/// <code>Atom</code> class is the atom particle effect.
/// It is not directly used in the code but it is the inclusion
/// of a portion of the assignment.
/// </summary>
/// <strong> Last Revised: Friday, December 17th, 2021 </strong>
class Atom: public Entity
{
    private:
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
    Atom();
    ~Atom();
    
    void render(const glm::mat4&, const glm::mat4&, const glm::mat4&) const;

};
#endif
