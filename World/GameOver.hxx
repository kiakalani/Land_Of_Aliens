#ifndef _GAME_OVER_HXX_
#define _GAME_OVER_HXX_
#include "GameWorld.hh"
#include "../Entity/Label.hh"
class GameOver: public GameWorld
{
    private:
    Label *game_over_message;
    Label *main_menu;

    public:
    GameOver(const bool&);
    void set_event_handlers();

    void update();

    static void on_mouse_pressed(int, void*);
};
#endif
