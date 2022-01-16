#include "Pause.hxx"
#include "../Entity/Label.hh"
#include <stdio.h>
#include "MainMenu.hxx"
#include "../Camera/Camera.hh"
Pause::Pause(GameWorld *g): paused_world(g), del_world(1)
{
    main_menu = new Label;
    main_menu->set_scale(glm::vec3(25.0f, 10.0f, 1.0f));
    main_menu->set_text((char*)"Back to Main Menu");
    main_menu->set_translate(glm::vec3(0.0f, -25.0f, 0.0f));
    add_entity(main_menu);

    resume = new Label;
    resume->set_translate(glm::vec3(0.0f, 10.0f, 0.0f));
    resume->set_text((char*)"Resume Game");
    resume->set_scale(glm::vec3(25.0f, 10.0f, 1.0f));
    add_entity(resume);

    paused = new Label;
    paused->set_text((char*)"Game Paused");
    paused->set_transparent(1);
    paused->set_translate(glm::vec3(0.0f, 35.0f, 0.0f));
    paused->set_scale(glm::vec3(25.0f, 10.0f, 1.0f));
    add_entity(paused);
    paused->set_text_color(80, 0, 150);

}   

void Pause::set_event_handlers()
{
    // GameDisplay::make_display()->reset_pointer();
    GameDisplay::make_display()->receive_pointer((Pause*)this);
    GameDisplay::make_display()->add_on_key_released(on_key_press);
    GameDisplay::make_display()->add_on_mouse_pressed(on_mouse_press);
}

void Pause::on_key_press(int k, void *ptrs)
{

    Pause *p = (Pause*)(((void**)ptrs)[0]);
    if (k == GLFW_KEY_ESCAPE)
    {
        p->del_world = 0;
        GameDisplay::make_display()->get_camera()->follow_entity((Entity*)p->paused_world->get_player());
        GameDisplay::make_display()->set_world(p->paused_world, 0);
        
    }
}

void Pause::on_mouse_press(int k, void *ptrs)
{
    Pause *p = (Pause*)(((void**)ptrs)[0]);

    if (p->main_menu->collided_mouse())
    {
        GameDisplay::make_display()->set_world(new MainMenu, 1);
    }
    if (p->resume->collided_mouse())
    {
        p->del_world = 0;
        
        GameDisplay::make_display()->set_world(p->paused_world, 0);
    }
}

Pause::~Pause()
{
    if (del_world) delete paused_world;
}

void Pause::update()
{
    select(main_menu);
    select(resume);
    GameWorld::update();
}

void Pause::select(Label *l)
{
    if (!l->collided_mouse())
    {
        l->set_text_color(150, 100, 0);
        l->set_background_color(80, 80, 80);
    }
    else
    {
        l->set_background_color(150, 100, 0);
        l->set_text_color(80, 80, 80);
    }
}