#include "MainMenu.hxx"
#include "BasicWorld.hxx"
#include "stdio.h"
#include "GamePage.hxx"
#include "../Game/Entity/Save.hxx"
#include "Instructions.hxx"
#include "../Entity/Entities/Atom.hxx"
MainMenu::MainMenu()
{
    set_up_new();
    set_up_load();
    set_up_quit();
    set_up_instructions();

}

void MainMenu::set_event_handlers()
{
    GameDisplay::make_display()->receive_pointer((void*)this);
    GameDisplay::make_display()->add_on_mouse_pressed(on_mouse_pressed);
}

void MainMenu::set_up_new()
{
    new_game = new Label;
    new_game->set_text((char*)"NEW GAME");
    new_game->set_translate(glm::vec3(0.0f, 20.0f, 0.0f));
    new_game->set_scale(glm::vec3(25.0, 5.0f, 1.0f));
    
    new_game->set_text_color(150, 100, 0);
    new_game->set_background_color(80, 80, 80);
    
    add_entity(new_game);
}

void MainMenu::set_up_load()
{
    load_game = new Label;
    load_game->set_text((char*)"LOAD GAME");
    load_game->set_scale(glm::vec3(25.0f, 5.0f, 1.0f));

    load_game->set_text_color(150, 100, 0);
    load_game->set_background_color(80, 80, 80);

    add_entity(load_game);
}

void MainMenu::set_up_instructions()
{
    instructions = new Label;
    instructions->set_text((char*)"INSTRUCTIONS");
    instructions->set_scale(glm::vec3(25.0f, 5.0f, 1.0f));
    instructions->set_translate(glm::vec3(0.0f, -20.0f, 0.0f));
    
    instructions->set_text_color(150, 100, 0);
    instructions->set_background_color(80, 80, 80);
    
    add_entity(instructions);
}

void MainMenu::set_up_quit()
{
    quit = new Label;
    quit->set_text((char*)"QUIT GAME");
    quit->set_scale(glm::vec3(25.0f, 5.0f, 1.0f));
    quit->set_translate(glm::vec3(0.0f, -40.0f, 0.0f));

    quit->set_text_color(150, 100, 0);
    quit->set_background_color(80, 80, 80);

    add_entity(quit);
}

bool MainMenu::mouse_collided(Label *&l) const
{
    float mx = GameDisplay::mouseXRel();
    float my = GameDisplay::mouseYRel();
    return mx >= l->get_position()[0] - l->get_scale()[0]
        && mx <= l->get_position()[0] + l->get_scale()[0]
        && my >= l->get_position()[1] - l->get_scale()[1]
        && my <= l->get_position()[1] + l->get_scale()[1];
    // return false;
}

void MainMenu::select(Label *l)
{
    l->set_text_color(80, 80, 80);
    l->set_background_color(150, 100, 0);
}

void MainMenu::unselect(Label *l)
{
    l->set_background_color(80, 80, 80);
    l->set_text_color(150, 100, 0);
}

void MainMenu::update()
{
    if (mouse_collided(new_game)) {
        select(new_game);
    } else {
        unselect(new_game);
    }
    if (mouse_collided(load_game)) {
        select(load_game);
    } else {
        unselect(load_game);
    }
    if (mouse_collided(instructions)) {
        select(instructions);
    } else {
        unselect(instructions);
    }
    if (mouse_collided(quit)) {
        select(quit);
    } else {
        unselect(quit);
    }
    GameWorld::update();
}

void MainMenu::on_mouse_pressed(int k, void *p)
{
    MainMenu *m = (MainMenu*)(((void**)p)[0]);
    if (m->mouse_collided(m->quit)) GameDisplay::make_display()->close_window();

    if (m->mouse_collided(m->new_game)) {
        
        
        GameDisplay::make_display()->set_world(new GamePage, 1);
        return;
    }

    if (m->mouse_collided(m->load_game))
    {
        GameDisplay::make_display()->set_world(new GamePage(Save::load_game()), 1);
        return;
    }

    if (m->mouse_collided(m->instructions))
    {
        GameDisplay::make_display()->set_world(new Instructions, 1);
    }

}