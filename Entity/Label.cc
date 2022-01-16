#include "Label.hh"
#include <string.h>
#include <stdio.h>

Label::Label(): Entity(GameDisplay::get_geometries()->QUAD(), GameDisplay::get_loaded_shaders()->LABEL(), GameDisplay::get_loaded_textures()->LABEL())
{
    memset(text, 0, sizeof(char) * 100);
    bg_color = glm::vec3(1.0f, 1.0f, 1.0f);
    text_color = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Label::set_text(char *tx)
{
    sprintf(text, "%s", tx);
}





void Label::render(const glm::mat4 &camera, const glm::mat4 &projection, const glm::mat4 &projection_2d) const
{
    setup_render_elems(camera, projection, projection_2d);
    char txt[15];
    shader->set_uniform_float((char*)"length_of_text", (float)(strlen(text)));
    shader->set_uniform_vec3((char*)"background", bg_color);
    shader->set_uniform_vec3((char*)"text_color", text_color);

    for (uint8_t i = 0; i < strlen(text); i++)
    {
        if (text[i] >= 65 && text[i] <= 90)
        {
            sprintf(txt, "xs[%u]", i);
            shader->set_uniform_float(txt, (text[i] - 65) * (1 / 26.0f));
            sprintf(txt, "ys[%u]", i);
            shader->set_uniform_float(txt, 0.0f);
        } 
        else if (text[i] >= 97 && text[i] <= 122)
        {
            sprintf(txt, "xs[%u]", i);
            shader->set_uniform_float(txt, (text[i] - 97) * (1 / 26.0f));
            sprintf(txt, "ys[%u]", i);
            shader->set_uniform_float(txt, 1.0f / 5.0f);
        }
        else if (text[i] >= 48 && text[i] <= 57)
        {
            sprintf(txt, "xs[%u]", i);
            shader->set_uniform_float(txt, (text[i] - 48) * (1 / 26.0f));
            sprintf(txt, "ys[%u]", i);
            shader->set_uniform_float(txt, 2.0f / 5.0f);
        } else if (text[i] == ':')
        {
            sprintf(txt, "xs[%u]", i);
            shader->set_uniform_float(txt, (10.0f / 25.0f));
            sprintf(txt, "ys[%u]", i);
            shader->set_uniform_float(txt, 2.0f / 5.0f);
        }
        else if (text[i] == ' ')
        {
            sprintf(txt, "xs[%u]", i);
            shader->set_uniform_float(txt, (11.0f / 25.0f));
            sprintf(txt, "ys[%u]", i);
            shader->set_uniform_float(txt, 2.0f / 5.0f);
        }
        else if (text[i] == '.')
        {
            sprintf(txt, "xs[%u]", i);
            shader->set_uniform_float(txt, (12.0f / 25.0f));
            sprintf(txt, "ys[%u]", i);
            shader->set_uniform_float(txt, 2.0f / 5.0f);
        }
    }
    setup_render_draw();
}

void Label::set_text_color(uint8_t r, uint8_t g, uint8_t b)
{
    text_color = glm::vec3(r / 255.0f, g / 255.0f, b / 255.0f);
}

void Label::set_background_color(uint8_t r, uint8_t g, uint8_t b)
{
    bg_color = glm::vec3(r / 255.0f, g / 255.0f, b / 255.0f);
}


bool Label::collided_mouse() const
{
    float mx = GameDisplay::mouseXRel();
    float my = GameDisplay::mouseYRel();
    return mx >= get_position()[0] - get_scale()[0]
        && mx <= get_position()[0] + get_scale()[0]
        && my >= get_position()[1] - get_scale()[1]
        && my <= get_position()[1] + get_scale()[1];
}