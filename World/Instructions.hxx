#ifndef _INSTRUCTIONS_HXX_
#define _INSTRUCTIONS_HXX_
#include "GameWorld.hh"
#include "../Entity/Label.hh"
class Instructions: public GameWorld
{
    Entity *explanation;

    Label *next;
    Label *prev;

    Texture *current_texture;
    char current_index;

    public:
    void update();
    Instructions();


    static void on_mouse_released(int, void*);

    void set_event_handlers();

};
#endif
