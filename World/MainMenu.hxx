#ifndef _MENU_HXX_
#define _MENU_HXX_
#include "GameWorld.hh"
#include "../Entity/Label.hh"
class MainMenu: public GameWorld
{
    private:
    Label *new_game;
    Label *load_game;
    Label *instructions;
    Label *quit;

    void set_up_new();
    void set_up_load();
    void set_up_instructions();
    void set_up_quit();

    public:
    MainMenu();

    void update();
    void set_event_handlers();
    
    private:
    static void on_mouse_pressed(int, void*);
    bool mouse_collided(Label*&) const;

    void select(Label*);
    void unselect(Label*);

};
#endif
