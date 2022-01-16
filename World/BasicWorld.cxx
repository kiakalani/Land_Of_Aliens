#include "BasicWorld.hxx"
#include "../Shader/Shader.hh"
#include "../Entity/Geometries/QuadGeometry.hxx"
#include "../Entity/Entity.hh"
#include "../Entity/Label.hh"
#include "../Texture/Texture.hh"
#include "../Display/GameDisplay.hh"
#include <stdio.h>
#include "../Entity/Geometries/SphereGeometry.hxx"
#include "../Entity/Geometries/MyTerrainGeometry.hxx"
#include "../Entity/Geometries/CylinderGeometry.hxx"
#include "../Camera/Camera.hh"
#include "../Game/Entity/SpaceSnail.hxx"
#include "../Game/Entity/GasStation.hxx"
#include "../Game/Entity/SpaceDragon.hxx"
#include "../Game/Entity/SpaceStoneMonster.hxx"
#include "../Game/Entity/Star.hxx"
#include "Pause.hxx"
BasicWorld::BasicWorld(): GameWorld()
{
    // Reading shaders
    text_shader = Shader::read_file((char*)SHADER_PATH"/Entity/Label/text_vert.glsl", (char*)SHADER_PATH"/Entity/Label/text_frag.glsl");
    progress_shader = Shader::read_file((char*)SHADER_PATH"/Entity/ProgressBar/TexturedProgress_vert.glsl",(char*)SHADER_PATH"/Entity/ProgressBar/TexturedProgress_frag.glsl");
    proc_sh = Shader::read_file((char*)SHADER_PATH"/procedural_vp.glsl", (char*)SHADER_PATH"/procedural_fp.glsl");

    // Reading textures
    text_table = new Texture((char*)TEXTURE_PATH"/alphabets.png");
    progress_txtr = new Texture((char*)TEXTURE_PATH"/progress.jpg");
    // Initiation of geometry
    q_geom = new QuadGeometry;
    c_geom = new SphereGeometry;
    GameDisplay::make_display()->get_camera()->set_position(glm::vec3(0.0f, 10.0f, 0.0f));
    terrain = new Terrain;
    
    add_entity(terrain);
    
    // MyTerrainGeometry *terrain = new MyTerrainGeometry; // height and depth are reversed
    // Entity *entity = new Entity(terrain, proc_sh, progress_txtr);
    // add_entity(entity);
    // entity->set_scale(glm::vec3(50.0f, 1.0f, 50.0f));
    // Initiation of buttons
    leftbtn = new Label;
    rightbtn = new Label;
    up_btn = new Label;
    down_btn = new Label;

    // Translation of buttons
    leftbtn->translate(glm::vec3(-25.0f, 0.0f, 0.0f));
    rightbtn->translate(glm::vec3(25.0f, 0.0f, 0.0f));
    up_btn->translate(glm::vec3(0.0f, 25.0f, 0.0f));
    down_btn->translate(glm::vec3(0.0f, -25.0f, 0.0f));

    // Scaling buttons
    leftbtn->set_scale(glm::vec3(10.0f, 5.0f, 1.0f));
    rightbtn->set_scale(glm::vec3(10.0f, 5.0f, 1.0f));
    up_btn->set_scale(glm::vec3(10.0f, 5.0f, 1.0f));
    down_btn->set_scale(glm::vec3(10.0f, 5.0f, 1.0f));

    // Setting text on buttons
    leftbtn->set_text((char*)"Decrease");
    rightbtn->set_text((char*)"Increase");
    up_btn->set_text((char*)"Click me");
    down_btn->set_text((char*)"For fun");

    // Loading buttons to the world
    // add_entity(leftbtn);
    // add_entity(rightbtn);
    // add_entity(up_btn);
    // add_entity(down_btn);

    // Initiation of progress bar
    // progress = new ProgressBar(q_geom, progress_shader, progress_txtr);
    // progress->set_scale(glm::vec3(5.0f, 2.0f, 0.0f));
    // add_entity(progress);
    // progress->set_progress(20.0f);

    count_up_clicks = 0;
    this->tank = new Tank();
    this->tank->translate(glm::vec3(50.0f, 5.0, 50.0f));
    add_entity(this->tank);

    player = tank;

    GameDisplay::make_display()->get_camera()->follow_entity(tank);
    GameDisplay::make_display()->get_camera()->set_position(glm::vec3(20.0f, 2.0f, 20.0f));
    leader = new GasStation;
    leader->translate(glm::vec3(80.0f, 80.0f, 80.0f));
    for (uint8_t i = 0; i < 2; ++i)
    {
        SpaceDragon *d = new SpaceDragon;
        d->set_translate(glm::vec3(rand() % 2000, 30.0f, rand() % 2000));
        add_entity(d);
        Star *s = new Star;
        s->set_translate(glm::vec3(rand() % 2000, 30.0f, rand() % 2000));
        add_entity(s);


        SpaceStoneMonster *ss = new SpaceStoneMonster;
        ss->set_translate(glm::vec3(rand() % 2000, 30.0f, rand() % 2000));
        add_entity(ss);

    }
    add_entity(leader);
}

void BasicWorld::set_event_handlers()
{
    GameDisplay::make_display()->add_on_key_pressed(onKeyPressed);
    GameDisplay::make_display()->add_on_key_released(onKeyReleased);
    GameDisplay::make_display()->add_on_mouse_pressed(onMousePressed);
    GameDisplay::make_display()->receive_pointer(this);
    GameDisplay::make_display()->receive_pointer(GameDisplay::make_display());

}


void BasicWorld::onKeyPressed(int key, void *ptrs)
{
    Camera *camera = ((GameDisplay*)(((void**)ptrs)[1]))->get_camera();
    Tank *t = ((BasicWorld*)((void**)ptrs)[0])->tank;
    switch (key)
    {
    case GLFW_KEY_LEFT:
        t->set_translate_speed(glm::vec3(-1.0f, 0.0f, 0.0f));
        break;
    case GLFW_KEY_RIGHT:
        t->set_translate_speed(glm::vec3(1.0f, 0.0f, 0.0f));
        break;
    case GLFW_KEY_UP:
        t->set_translate_speed(glm::vec3(0.0f, 0.0f, 1.0f));
        break;
    case GLFW_KEY_DOWN:
        t->set_translate_speed(glm::vec3(0.0f, 0.0f, -1.0f));
        break;
    case GLFW_KEY_W:
        camera->set_forward_speed(1.0f);
        break;
    case GLFW_KEY_S:
        camera->set_forward_speed(-1.0f);
        break;
    case GLFW_KEY_Q:
        t->rotate_gun_pipe(0.1f);
        break;
    case GLFW_KEY_E:
        t->rotate_gun_pipe(-.1f);
        break;
    case GLFW_KEY_ESCAPE:
        {
            GameDisplay::make_display()->set_world(new Pause(((BasicWorld*)((void**)ptrs)[0])), 0);
        }
    default:
        break;
    }
}
void BasicWorld::onKeyReleased(int key, void *ptrs)
{
    Camera *camera = ((GameDisplay*)(((void**)ptrs)[1]))->get_camera();
    Tank *t = ((BasicWorld*)((void**)ptrs)[0])->tank;
    switch (key)
    {
    case GLFW_KEY_LEFT:
        t->set_translate_speed(glm::vec3(-t->get_translate_speed()[0], 0.0f, 0.0f));
        break;
    case GLFW_KEY_RIGHT:
        t->set_translate_speed(glm::vec3(-t->get_translate_speed()[0], 0.0f, 0.0f));
        break;
    case GLFW_KEY_UP:
        t->set_translate_speed(glm::vec3(0.0f, 0.0f, -t->get_translate_speed()[2]));
        break;
    case GLFW_KEY_DOWN:
        t->set_translate_speed(glm::vec3(0.0f, 0.0f, -t->get_translate_speed()[2]));
        break;
    case GLFW_KEY_W:
        // t->rotate_gun_pipe_up_down(-0.1f);
        break;
    case GLFW_KEY_S:
        // t->rotate_gun_pipe_up_down(0.1f);
        break;
    case GLFW_KEY_I:
        t->rotate(glm::angleAxis(1.0f, glm::vec3(1.0f, 0.0f, 0.0f)));
        break;
    case GLFW_KEY_Q:
        camera->set_roll_speed(0.0f);
        break;
    case GLFW_KEY_E:
        camera->set_roll_speed(0.0f);
        break;
    case GLFW_KEY_M:
        t->shoot();
    default:
        break;
    }
}
BasicWorld::~BasicWorld()
{
    delete text_table;
    delete progress_txtr;
    delete text_shader;
    delete progress_shader;
    delete q_geom;
    
}

void BasicWorld::update()
{
    // leader->dance();
    Camera *camera = GameDisplay::make_display()->get_camera();
    // tank->set_translate(camera->get_position() + camera->get_forward() * 70.0f);
    // tank->translate(glm::vec3(0.0f, +4.0f, 0.0f));
    
    // right button collision detection
    glm::vec3 rightbtnpos = rightbtn->get_position();
    glm::vec3 rightbtnscale = rightbtn->get_scale();

    // leader->set_translate(tank->get_position());
    if (GameDisplay::mouseXRel() > rightbtnpos.x - rightbtnscale.x && GameDisplay::mouseXRel() < rightbtnpos.x + rightbtnscale.x)
    {
        if (GameDisplay::mouseYRel() > rightbtnpos.y - rightbtnscale.y && GameDisplay::mouseYRel() < rightbtnpos.y + rightbtnscale.y)
        {
            rightbtn->set_background_color(0, 0, 200);
        }
    } else rightbtn->set_background_color(255, 255, 255);

    // Left button collision detection
    glm::vec3 leftbtnpos = leftbtn->get_position();
    glm::vec3 leftbtnscale = leftbtn->get_scale();
    if (GameDisplay::mouseXRel() > leftbtnpos.x - leftbtnscale.x && GameDisplay::mouseXRel() < leftbtnpos.x + leftbtnscale.x)
    {
        if (GameDisplay::mouseYRel() > leftbtnpos.y - leftbtnscale.y && GameDisplay::mouseYRel() < leftbtnpos.y + leftbtnscale.y)
        {
            leftbtn->set_background_color(200, 0, 0);
        }
    } else leftbtn->set_background_color(255, 255, 255);

    

    GameWorld::update();
}

void BasicWorld::onMousePressed(int key, void *pointers)
{
    
    BasicWorld *world = (BasicWorld*)((void**)(pointers))[0];
    if (key == GLFW_MOUSE_BUTTON_LEFT)
    {
        // Right button collision detection
        glm::vec3 rightbtnpos = world->rightbtn->get_position();
        glm::vec3 rightbtnscale = world->rightbtn->get_scale();

        if (GameDisplay::mouseXRel() > rightbtnpos.x - rightbtnscale.x && GameDisplay::mouseXRel() < rightbtnpos.x + rightbtnscale.x)
        {
            if (GameDisplay::mouseYRel() > rightbtnpos.y - rightbtnscale.y && GameDisplay::mouseYRel() < rightbtnpos.y + rightbtnscale.y)
            {
                world->progress->set_progress(world->progress->get_progress() + 5.0f);
            }
        }

        // Left button collision detection
        glm::vec3 leftbtnpos = world->leftbtn->get_position();
        glm::vec3 leftbtnscale = world->leftbtn->get_scale();
        if (GameDisplay::mouseXRel() > leftbtnpos.x - leftbtnscale.x && GameDisplay::mouseXRel() < leftbtnpos.x + leftbtnscale.x)
        {
            if (GameDisplay::mouseYRel() > leftbtnpos.y - leftbtnscale.y && GameDisplay::mouseYRel() < leftbtnpos.y + leftbtnscale.y)
            {
                world->progress->set_progress(world->progress->get_progress() - 5.0f);
            }
        }

        // Up button collision detection
        glm::vec3 upbtnpos = world->up_btn->get_position();
        glm::vec3 upbtnscale = world->up_btn->get_scale();
        if (GameDisplay::mouseXRel() > upbtnpos.x - upbtnscale.x && GameDisplay::mouseXRel() < upbtnpos.x + upbtnscale.x)
        {
            if (GameDisplay::mouseYRel() > upbtnpos.y - upbtnscale.y && GameDisplay::mouseYRel() < upbtnpos.y + upbtnscale.y)
            {
                char *text_sent = new char[30];
                sprintf(text_sent, "Clicked %u times", ++(world->count_up_clicks));
                world->up_btn->set_text(text_sent);
                delete[] text_sent;
            }
        }

        // Down button collision detection
        glm::vec3 downbtnpos = world->down_btn->get_position();
        glm::vec3 downbtnscale = world->down_btn->get_scale();
        if (GameDisplay::mouseXRel() > downbtnpos.x - downbtnscale.x && GameDisplay::mouseXRel() < downbtnpos.x + downbtnscale.x)
        {
            if (GameDisplay::mouseYRel() > downbtnpos.y - downbtnscale.y && GameDisplay::mouseYRel() < downbtnpos.y + downbtnscale.y)
            {
                world->down_btn->set_background_color(rand() % 255, rand() % 255, rand() % 255);
                world->down_btn->set_text_color(rand() % 255, rand() % 255, rand() % 255);
            }
        }
        
    }
}
