#include "Atom.hxx"
#include <string.h>
#include <stdio.h>

Atom::Atom(): Entity(GameDisplay::get_geometries()->CYLINDER(), GameDisplay::get_loaded_shaders()->ATOM(), GameDisplay::get_loaded_textures()->GAS_STATION())
{
    count_multiples = 200; 

    x_multiples = new float[count_multiples];
    particles = new glm::vec3[count_multiples];
    y_multiples = new float[count_multiples];
    z_multiples = new float[count_multiples];
    for (uint32_t i = 0; i < count_multiples >> 2; ++i) {
        float xmult = (float)rand() / RAND_MAX; // randomized x angle for orbit
        float ymult = (float)rand() / RAND_MAX; // randomized y angle for orbit
        glm::vec3 particle = glm::vec3((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX); // random position for a particle
        float zmult = (float)rand() / RAND_MAX; // randomized z angle for orbi
        for (uint8_t j = 0; j < 4; ++j) // Basically four spheres per orbit
        {
        x_multiples[4 * i + j] = xmult;
        y_multiples[4 * i + j] = ymult;
        particles[4 * i + j] = particle;
        particles[4 * i + j] = glm::normalize(particles[4 *i + j]);
        z_multiples[4 * i + j] = zmult;
        }
    }
    set_count_duplicates(count_multiples + 1); // 1 for the circle in center and 
    // the rest for the circles around the atom
    set_transparent(1);

}

void Atom::render(const glm::mat4 &view, const glm::mat4 &projection, const glm::mat4 &projection_2d) const
{
    setup_render_elems(view, projection, projection_2d);
    for (uint32_t i = 0; i < count_multiples; ++i)
    { // Sending all of the x multiples to the shader
        char name[20];
        sprintf(name, "xmult[%u]", i);
        shader->set_uniform_float(name, x_multiples[i]);
        sprintf(name, "positions[%u]", i);
        shader->set_uniform_vec3(name, particles[i]);
        sprintf(name, "ymult[%u]", i);
        shader->set_uniform_float(name, y_multiples[i]);
        sprintf(name, "zmult[%u]", i);
        shader->set_uniform_float(name, z_multiples[i]);
    }
    setup_render_draw();
}


