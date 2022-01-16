#include "SphereExplosion.hxx"
#include "../Geometries/SphereGeometry.hxx"
#include <stdio.h>
SphereExplosion::SphereExplosion(): Entity(GameDisplay::get_geometries()->SPHERE(), GameDisplay::get_loaded_shaders()->SPHERE_EXPLOSION())
{
    explosion_angles = new float[count_explosion_angles = 200];
    expx = new float[count_explosion_angles];
    expy = new float[count_explosion_angles];
    for (uint32_t i = 0; i < count_explosion_angles; ++i){
        explosion_angles[i] =((float)rand() / RAND_MAX) ;
        expx[i] = ((float)rand() / RAND_MAX) ;
        expy[i] =  ((float)rand() / RAND_MAX) ;
    } 
    set_count_duplicates(count_explosion_angles);
    set_translate(glm::vec3(1.0, 1.0, 0.0));
    set_scale(glm::vec3(6.0f, 6.0f, 6.0f));
    // set_transparent(1);

    appearance = glfwGetTime();
}


void SphereExplosion::render(const glm::mat4 &view, const glm::mat4 &projec, const glm::mat4 &p4oj_2d) const
{
    setup_render_elems(view, projec, p4oj_2d);
    for (uint32_t i = 0; i < count_explosion_angles; ++i) // sending uniforms
    {
        char name[20];
        sprintf(name, "anglex[%u]", i);
        shader->set_uniform_float(name, explosion_angles[i]);

        sprintf(name, "angley[%u]", i);
        shader->set_uniform_float(name, expx[i]);

        sprintf(name, "anglez[%u]", i);
        shader->set_uniform_float(name, expy[i]);
    }
    setup_render_draw();
}


void SphereExplosion::update()
{
    if (glfwGetTime() - appearance >= 1.0f) remove();
}