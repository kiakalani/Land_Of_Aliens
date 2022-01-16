#include "../includes.hxx"

#include "../World/MainMenu.hxx"
#include "../Display/GameDisplay.hh"


int main()
{
    GameDisplay *display = GameDisplay::make_display();
    
    display->set_world(new MainMenu);

    display->execute();

    delete display;
    
    return 0;
}
