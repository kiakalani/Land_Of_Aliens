#ifndef _PAUSE_HXX_
#define _PAUSE_HXX_
#include "GameWorld.hh"
class Label;
class Pause: public GameWorld
{
    private:
    GameWorld *paused_world;
    bool del_world;//set true by default and only when false it that we go back to game from pause menu
    Label *paused;
    Label *resume;
    Label *main_menu;

    static void on_key_press(int, void*);
    static void on_mouse_press(int, void*);
    public:
    Pause(GameWorld*);
    ~Pause();

    void update();
    void set_event_handlers();
    void select(Label*);
    void unselect(Label*);
};

#endif
