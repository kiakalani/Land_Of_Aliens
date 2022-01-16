#include "ProgressBar.hxx"
#include "../World/GameWorld.hh"
ProgressBar::ProgressBar(Texture *tx): Entity(GameDisplay::get_geometries()->QUAD(),
 GameDisplay::get_loaded_shaders()->PROGRESS_BAR(), tx)
{
    progress = 0.0f;
    set_transparent(1);
}

void ProgressBar::set_progress(float percentage)
{
    progress = percentage * 0.01f;
    if (progress > 100.0f) progress = 100.0f;
    else if (progress < 0.0f) progress = 0.0f;
}

float ProgressBar::get_progress() const
{
    return (progress * 100.0f);
}

void ProgressBar::render(const glm::mat4 &cam, const glm::mat4 &proj, const glm::mat4 &proj_2d) const
{
    setup_render_elems(cam, proj, proj_2d);
    shader->set_uniform_float((char*)"progress", progress);
    setup_render_draw();
}