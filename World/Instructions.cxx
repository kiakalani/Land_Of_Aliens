#include "Instructions.hxx"
#include "MainMenu.hxx"


Instructions::Instructions()
{
    explanation = new Entity(GameDisplay::get_geometries()->QUAD(), GameDisplay::get_loaded_shaders()->WHITE_TPARENT(), GameDisplay::get_loaded_textures()->INSTRUCTIONS(0));
    current_index = 0;
    current_texture = GameDisplay::get_loaded_textures()->INSTRUCTIONS((uint8_t)current_index);
    explanation->set_scale(glm::vec3(50.0f, 50.0f, 1.0f));
    add_entity(explanation);

    prev = new Label;
    prev->set_text((char*)"Previous");
    next = new Label;
    next->set_text((char*)"Next");
    add_entity(prev);
    add_entity(next);

    prev->set_scale(glm::vec3(10.0f, 5.0f, 1.0f));
    next->set_scale(glm::vec3(10.0f, 5.0f, 1.0f));

    prev->set_translate(glm::vec3(-40.0f, -40.0f, 1.0f));
    next->set_translate(glm::vec3(40.0f, -40.0f, 1.0f));

    prev->set_text_color(200, 100, 0);
    prev->set_background_color(100, 200, 0);
    next->set_text_color(200, 100, 0);
    next->set_background_color(100, 200, 0);
}


void Instructions::update()
{
    if (prev->collided_mouse())
    {
        prev->set_background_color(200, 100, 0);
        prev->set_text_color(100, 200, 0);
    }
    else
    {
        prev->set_text_color(200, 100, 0);
        prev->set_background_color(100, 200, 0);
    }

    if (next->collided_mouse())
    {
        next->set_background_color(200, 100, 0);
        next->set_text_color(100, 200, 0);
    }
    else
    {
        next->set_text_color(200, 100, 0);
        next->set_background_color(100, 200, 0);
    }
}


void Instructions::set_event_handlers()
{
    GameDisplay::make_display()->receive_pointer((void*)this);
    GameDisplay::make_display()->add_on_mouse_released(on_mouse_released);
}



void Instructions::on_mouse_released(int k, void *ptrs)
{
    Instructions *i = (Instructions*)(((void**)ptrs)[0]);
    if (i->next->collided_mouse())
    {
        i->current_index++;
    }
    else if (i->prev->collided_mouse())
    {
        i->current_index--;
    }
    if (i->current_index < 0 || i->current_index >= COUNT_INSTRUCTIONS)
    {
        GameDisplay::make_display()->set_world(new MainMenu, 1);
    }
    else
    {
        i->current_texture = GameDisplay::get_loaded_textures()->INSTRUCTIONS(i->current_index);
        i->explanation->set_texture(i->current_texture);
    }
}