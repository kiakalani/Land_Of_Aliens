#include "GameOver.hxx"
#include <stdio.h>
#include "MainMenu.hxx"
GameOver::GameOver(const bool &win)
{
    game_over_message = new Label;
    char win_message[20];
    sprintf(win_message, "You %s", win ? "Win" : "Lose");
    game_over_message->set_text(win_message);

    game_over_message->set_transparent(1);
    game_over_message->set_text_color(200, 100, 0);
    game_over_message->set_scale(glm::vec3(25.0f, 20.0f, 1.0f));
    add_entity(game_over_message);

    sprintf(win_message, "Main Menu");

    main_menu = new Label;
    main_menu->set_text(win_message);
    add_entity(main_menu);
    main_menu->set_scale(glm::vec3(20.0f, 5.0f, 1.0f));
    main_menu->set_translate(glm::vec3(-20.0f, -40.0f, 0.0f));

    main_menu->set_background_color(0, 200, 100);
    main_menu->set_text_color(200, 100, 0);
}


void GameOver::update()
{
    if (main_menu->collided_mouse())
    {
        main_menu->set_text_color(0, 200, 100);
        main_menu->set_background_color(200, 100, 0);
    } else {
        main_menu->set_background_color(0, 200, 100);
        main_menu->set_text_color(200, 100, 0);
    }
}


void GameOver::on_mouse_pressed(int k, void *args)
{
    GameOver *g = (GameOver*)(((void**)(args))[0]);
    if (g->main_menu->collided_mouse())
    {
        GameDisplay::make_display()->set_world(new MainMenu, 1);
    }
}


void GameOver::set_event_handlers()
{
    GameDisplay::make_display()->receive_pointer((void*)this);
    GameDisplay::make_display()->add_on_mouse_released(on_mouse_pressed);
}