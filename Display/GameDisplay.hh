#ifndef _GAME_DISPLAY_HH_
#define _GAME_DISPLAY_HH_
#include "../includes.hxx"
#include <stdint.h>
class Camera;
class GameWorld;
class LoadedShaders;
class Geometries;
class LoadedTextures;
/// <h2> Author: Kia Kalani </h2>
/// <strong> Student ID: 101145220 </strong>
/// <summary>
/// <code>GameDisplay</code> class is responsible for opening
/// a new display for the game. This class also handles mouse
/// events, and keyboard events.
/// It also contains the camera class for showing the view to
/// the player.
/// </summary>
/// <strong> Last revised: Thursday November 18th, 2021 </strong>
 
class GameDisplay
{
    private:
    static LoadedShaders *loaded_shaders;
    static Geometries    *geometries;
    static LoadedTextures *loaded_textures;
    bool wait;

    GameWorld *del_qd;
    // For putting a little bit of delay between every time we render and 
    // update components
    double last_tick;
    // Name definition of Function pointers for mouse and keyboard events
    typedef void (*MMFuncType)(double, double, void*);
    typedef void (*PIVFuncType)(int, void*);
    GLFWwindow *window;
    Camera *camera;
    // Callback functions for handling events
    static void resize_function(GLFWwindow*, int, int);
    static void mouse_moved_cb(GLFWwindow*, double, double); 
    static void mouse_ivk_cb(GLFWwindow*, int, int, int); 
    static void keyboard_ivk_cb(GLFWwindow*, int, int, int, int); 

    // Dynamic arrays for events. After writing it, I noticed this was not needed but it would
    // be a good touch to keep for bigger projects.
    PIVFuncType *mouse_pressed;
    PIVFuncType *mouse_released;
    PIVFuncType *key_pressed;
    PIVFuncType *key_released;
    MMFuncType *mouse_moved;    
    
    // Count of elements in dynamic arrays
    uint16_t count_mouse_pressed;
    uint16_t count_mouse_released;
    uint16_t count_mouse_moved;
    uint16_t count_key_pressed;
    uint16_t count_key_released;
    
    // Size of allocation for the dynamic arrays for event handling
    uint16_t m_p_n, m_r_n, m_m_n, k_p_n, k_r_n;

    // Width and height of screen
    static uint16_t width, height;

    static double mouse_x, mouse_y;
    
    // The current game world that we are rendering
    GameWorld *current_world;

    // A dynamic array of pointers that user sends to the display for
    // event handling.
    void **sent_ptr_by_user;

    // Count of elements and size of the dynamic array for event handling
    // dynamic array
    uint16_t count_ptrs, ptrs_n;

    GameDisplay(uint16_t = 1024, uint16_t = 768, char* = (char*)"Display");
    // Singelton for display instance
    static GameDisplay *disp;

    public:
    static double mouseX();
    static double mouseY();

    // Mouse position between 0 and 1
    static double mouseXRel();
    static double mouseYRel(); 

    // For singleton
    static GameDisplay *make_display(uint16_t = 1024, uint16_t = 768, char* = (char*)"Display");

    ~GameDisplay();
    void set_camera(Camera*);
    
    // Starting the game loop
    void execute();

    // Changing the game world that is being shown
    void set_world(GameWorld*, bool = 0);

    GameWorld *get_current_game_world() const;

    // Adding event handlers
    void add_on_mouse_moved(void(*)(double, double, void*)); 
    void add_on_mouse_pressed(void(*)(int, void*)); 
    void add_on_mouse_released(void(*)(int, void*)); 

    void add_on_key_pressed(void(*)(int, void*)); 
    void add_on_key_released(void(*)(int, void*)); 

    // Needed when we are switching the game worlds
    void remove_handler(void*); 

    Camera *get_camera() const;

    // Adding a pointer to the pointers array for event handling
    void receive_pointer(void*);

    // Deallocates the event handling pointer
    void reset_pointer();

    void close_window();

    void reset_event_handlers();

    void reset_camera();

    static LoadedShaders *get_loaded_shaders();
    static Geometries    *get_geometries();
    static LoadedTextures *get_loaded_textures();
    static uint16_t get_width();
    static uint16_t get_height();
};


#endif