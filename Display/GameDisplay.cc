#include "GameDisplay.hh"
#include <stdio.h>
#include "../Camera/Camera.hh"
#include "../World/GameWorld.hh"
#include <stdlib.h>
#include "../Shader/LoadedShaders.hxx"
#include "../Entity/Geometries/Geometries.hxx"
#include "../Texture/LoadedTextures.hxx"

uint16_t GameDisplay::width = 1024;
uint16_t GameDisplay::height = 768;
double GameDisplay::mouse_x = 0;
double GameDisplay::mouse_y = 0;

// The shaders, textures and geomteries all here for being
// accessed statically
LoadedShaders *GameDisplay::loaded_shaders = NULL;
Geometries    *GameDisplay::geometries = NULL;
LoadedTextures *GameDisplay::loaded_textures = NULL;

GameDisplay *GameDisplay::disp = NULL;

GameDisplay *GameDisplay::make_display(uint16_t width, uint16_t height, char *title)
{
    if (!disp)
    {
        disp = new GameDisplay(width, height, title);
    }
    return disp;
}

GameDisplay::GameDisplay(uint16_t width, uint16_t height, char *title):
camera(new Camera), mouse_pressed(NULL), mouse_released(NULL), key_pressed(NULL),
key_released(NULL), mouse_moved(NULL), count_mouse_pressed(0), count_mouse_released(0),
count_mouse_moved(0), count_key_pressed(0), count_key_released(0), m_p_n(0), m_r_n(0), m_m_n(0),
k_p_n(0), k_r_n(0), current_world((GameWorld*)0), sent_ptr_by_user((void**)0), count_ptrs(0), ptrs_n(0),
wait(0), del_qd((GameWorld*)0)
{
    last_tick = 0.0;
    this->width = width;
    this->height = height;
    if (!glfwInit())
    {
        printf("Error initializing the window\n");
        glfwTerminate();
        exit(-1);
    }
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window)
    {
        printf("Error opening window\n");
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);
    glewExperimental = 1;
    if (glewInit() != GLEW_OK)
    {
        printf("Error initializing glew\n");
        glfwTerminate();
        exit(-1);
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glViewport(0, 0, (int)width, (int)height);

    glfwSetWindowUserPointer(window, (void*)this);

    glfwSetFramebufferSizeCallback(window, resize_function);
    glfwSetCursorPosCallback(window, mouse_moved_cb);
    glfwSetKeyCallback(window, keyboard_ivk_cb);
    glfwSetMouseButtonCallback(window, mouse_ivk_cb);
    camera->set_projection(width, height);
    loaded_shaders = new LoadedShaders;
    geometries = new Geometries;
    loaded_textures = new LoadedTextures;
}

void GameDisplay::set_world(GameWorld *world, bool rem)
{
    if (current_world && rem)
    {
        reset_event_handlers();

        world->set_event_handlers();
        del_qd = current_world;
        current_world = world;

        GameWorld *d = del_qd;
        del_qd = NULL;
        delete d;
        
        
    } else {
        current_world = world;
        reset_event_handlers();

        world->set_event_handlers();
    }
        
}


GameDisplay::~GameDisplay()
{
    glfwDestroyWindow(window);
    glfwTerminate();
    delete camera;
    delete[] mouse_moved;
    delete[] mouse_pressed;
    delete[] mouse_released;
    delete[] key_pressed;
    delete[] key_released;
    reset_pointer();
    delete loaded_shaders;
    delete geometries;
    delete loaded_textures;
}

LoadedShaders *GameDisplay::get_loaded_shaders()
{
    return loaded_shaders;
}

Geometries    *GameDisplay::get_geometries()
{
    return geometries;
}

LoadedTextures *GameDisplay::get_loaded_textures()
{
    return loaded_textures;
}

void GameDisplay::set_camera(Camera *c)
{
    Camera *temp = camera;
    camera = c;
    delete temp;
    camera->set_projection(width, height);
    
}

double GameDisplay::mouseX()
{
    return mouse_x;
}

double GameDisplay::mouseY()
{
    return mouse_y;
}

double GameDisplay::mouseXRel()
{
    
    return ((mouse_x / (double)width) * 100.0) - 50.0;
}

double GameDisplay::mouseYRel()
{
    return -(((mouse_y / (double)height) * 100.0) - 50.0);
}


void GameDisplay::resize_function(GLFWwindow *window, int wid, int hei)
{
    GameDisplay *disp = (GameDisplay*) glfwGetWindowUserPointer(window);
    disp->width = (uint16_t) wid;
    disp->height = (uint16_t) hei;
    glViewport(0, 0, wid, hei);
    disp->camera->set_projection(width, height);
}

void GameDisplay::mouse_moved_cb(GLFWwindow *wind, double x, double y)
{
    GameDisplay *disp = (GameDisplay*) glfwGetWindowUserPointer(wind);
    for (uint16_t i = 0; i < disp->count_mouse_moved; ++i)
    disp->mouse_moved[i](x, y, (void*)disp->sent_ptr_by_user);
    GameDisplay::mouse_x = x;
    GameDisplay::mouse_y = y;

}

void GameDisplay::mouse_ivk_cb(GLFWwindow *wind, int btn, int action, int mods)
{
    GameDisplay *disp = (GameDisplay*) glfwGetWindowUserPointer(wind);
    if (action == GLFW_PRESS)
    {
        for (uint16_t i = 0; i < disp->count_mouse_pressed; ++i) {
            disp->mouse_pressed[i](btn, (void*)disp->sent_ptr_by_user);
        }
    }
    if (action == GLFW_RELEASE) {
        for (uint16_t i = 0; i < disp->count_mouse_released; ++i) {
            disp->mouse_released[i](btn, (void*)disp->sent_ptr_by_user);
        }
    }
}


void GameDisplay::keyboard_ivk_cb(GLFWwindow *wind, int key, int scancode, int action, int mods)
{
    GameDisplay *disp = (GameDisplay*) glfwGetWindowUserPointer(wind);
    if (action == GLFW_PRESS) {
        for (uint16_t i = 0; i < disp->count_key_pressed; ++i) {
            disp->key_pressed[i](key, (void*)disp->sent_ptr_by_user);
        }
        
    }

    if (action == GLFW_RELEASE) {
        for (uint16_t i = 0; i < disp->count_key_released; ++i) {
            disp->key_released[i](key, (void*)disp->sent_ptr_by_user);
        }
    }
}


void GameDisplay::add_on_mouse_moved(void (*handle)(double, double, void*)) {
    if (!count_mouse_moved) {
        mouse_moved = new MMFuncType[m_m_n = 1];
    } else if (count_mouse_moved + 1 >= m_m_n) {
        MMFuncType *funcs = new MMFuncType[m_m_n *= 2];
        for (uint16_t i = 0; i < count_mouse_moved; ++i) {
            funcs[i] = mouse_moved[i];
        }
        MMFuncType *del = mouse_moved;
        mouse_moved = funcs;
        delete[] del;
    }
    mouse_moved[count_mouse_moved++] = handle;
}


void GameDisplay::add_on_mouse_pressed(void(*handle)(int, void*)) {
    if (!count_mouse_pressed) {
        mouse_pressed = new PIVFuncType[m_p_n = 1];
    } else if (count_mouse_pressed + 1 >= m_p_n) {
        PIVFuncType *funcs = new PIVFuncType[m_p_n *= 2];
        for (uint16_t i = 0; i < count_mouse_pressed; ++i) {
            funcs[i] = mouse_pressed[i];
        }
        PIVFuncType *del = mouse_pressed;
        mouse_pressed = funcs;
        delete[] del;
    }
    mouse_pressed[count_mouse_pressed++] = handle;
}

void GameDisplay::add_on_mouse_released(void(*handle)(int, void*)) {
    if (!count_mouse_released) {
        mouse_released = new PIVFuncType[m_r_n = 1];
    } else if (count_mouse_released + 1 >= m_r_n) {
        PIVFuncType *funcs = new PIVFuncType[m_r_n *= 2];
        for (uint16_t i = 0; i < count_mouse_released; ++i) {
            funcs[i] = mouse_released[i];
        }
        PIVFuncType *del = mouse_released;
        mouse_released = funcs;
        delete[] del;
    }
    mouse_released[count_mouse_released++] = handle;
}

void GameDisplay::add_on_key_pressed(void(*handle)(int, void*)) {
    if (!count_key_pressed) {
        key_pressed = new PIVFuncType[k_p_n = 1];
    } else if (count_key_pressed + 1 >= k_p_n) {
        PIVFuncType *funcs = new PIVFuncType[k_p_n *= 2];
        for (uint16_t i = 0; i < count_key_pressed; ++i) {
            funcs[i] = key_pressed[i];
        }
        PIVFuncType *del = key_pressed;
        key_pressed = funcs;
        delete[] del;
    }
    key_pressed[count_key_pressed++] = handle;

}

void GameDisplay::add_on_key_released(void(*handle)(int, void*)) {
    if (!count_key_released) {
        key_released = new PIVFuncType[k_r_n = 1];
    } else if (count_key_released + 1 >= k_r_n) {
        PIVFuncType *funcs = new PIVFuncType[k_r_n *= 2];
        for (uint16_t i = 0; i < count_key_released; ++i) {
            funcs[i] = key_released[i];
        }
        PIVFuncType *del = key_released;
        key_released = funcs;
        delete[] del;
    }
    key_released[count_key_released++] = handle;
}

void GameDisplay::remove_handler(void *handler)
{
    for (uint16_t i = 0; i < count_key_pressed; ++i) {
        if ((void*)(key_pressed) == handler) {
            for (uint16_t j = i; j < count_key_pressed - 1; ++j) {
                key_pressed[j] = key_pressed[j + 1];
            }
            --count_key_pressed;
            return;
        }
    }

    for (uint16_t i = 0; i < count_key_released; ++i) {
        if ((void*)(key_released[i]) == handler) {
            for (uint16_t j = i; j < count_key_released - 1; ++j) {
                key_released[j] = key_released[j + 1];
            }
            --count_key_released;
            return;
        }
    }

    for (uint16_t i = 0; i < count_mouse_moved; ++i) {
        if ((void*)(mouse_moved[i]) == handler) {
            for (uint16_t j = i; j < count_mouse_moved - 1; ++j) {
                mouse_moved[j] = mouse_moved[j + 1];
            }
            --count_mouse_moved;
            return;
        }
    }

    for (uint16_t i = 0; i < count_mouse_pressed; ++i) {
        if ((void*)(mouse_pressed[i]) == handler) {
            for (uint16_t j = i; j < count_mouse_pressed - 1; ++j) {
                mouse_pressed[j] = mouse_pressed[j + 1];
            }
            --count_mouse_pressed;
            return;
        }
    }

    for (uint16_t i = 0; i < count_mouse_released; ++i) {
        if ((void*)(mouse_released[i]) == handler) {
            for (uint16_t j = i; j < count_mouse_released; ++j) {
                mouse_released[j] = mouse_released[j + 1];
            }
            --count_mouse_released;
            return;
        }
    }
}


void GameDisplay::execute()
{
    while (!glfwWindowShouldClose(window)) {
        double current_time = glfwGetTime();
        

        if (current_time - last_tick > 0.02) {
            // Render and update
            glClearColor(0.0f, 0.0f, 0.2f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            if (current_world)
            {
                current_world->update();
                current_world->render(camera);
                

            }
            camera->update();
            
            last_tick = current_time;
        }

        

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
}

Camera *GameDisplay::get_camera() const
{
    return camera;
}

void GameDisplay::reset_pointer()
{
    if (sent_ptr_by_user)
    {
        void **dels = sent_ptr_by_user;

        sent_ptr_by_user = (void**)0;
        delete[] dels;
        count_ptrs = ptrs_n = 0;
    }
    
}

void GameDisplay::receive_pointer(void *ptr)
{
    if (!sent_ptr_by_user)
    {
        sent_ptr_by_user = new void*[(ptrs_n = 1)];
    } else if (count_ptrs + 1 >= ptrs_n)
    {
        void **temp = new void*[ptrs_n *= 2];
        for (uint32_t i = 0; i < count_ptrs; ++i)
            temp[i] = sent_ptr_by_user[i];
        void **del = sent_ptr_by_user;
        sent_ptr_by_user = temp;
        delete[] del;
    }

    sent_ptr_by_user[count_ptrs++] = ptr;


}

void GameDisplay::close_window()
{
    glfwSetWindowShouldClose(window, 1);
}

GameWorld *GameDisplay::get_current_game_world() const
{
    return current_world;
}

void GameDisplay::reset_event_handlers()
{
    if (key_pressed)
    {
    PIVFuncType *kp = key_pressed;
    key_pressed = NULL;
    delete[] kp;
    k_p_n = count_key_pressed = 0;
    }

    if (key_released)
    {
    PIVFuncType *kr = key_released;
    key_released = NULL;
    delete[] kr;
    k_r_n = count_key_released = 0;
    }

    if (count_mouse_pressed)
    {
    PIVFuncType *mp = mouse_pressed;
    mouse_pressed = NULL;
    delete[] mp;
    m_p_n = count_mouse_pressed = 0;
    }

    if (mouse_released)
    {
    PIVFuncType *mr = mouse_released;
    mouse_released = NULL;
    delete[] mr;
    m_r_n = count_mouse_released = 0;
    }

    reset_pointer();

    // MMFuncType *mm = mouse_moved;
    // mouse_moved = NULL;
    // delete mm;
    // count_mouse_moved = m_m_n = 0;
}


void GameDisplay::reset_camera()
{
    set_camera(new Camera);
    // Camera *del = camera;
    // camera = new Camera;
    // delete del;
}

uint16_t GameDisplay::get_width()
{
    return width;
}

uint16_t GameDisplay::get_height()
{
    return height;
}