#include "LoadedShaders.hxx"
#include "../World/GameWorld.hh"

LoadedShaders::LoadedShaders()
{
    create_procedural();
    create_textured();
    create_label();
    create_colored();
    white_tparent = Shader::read_file((char*)SHADER_PATH"/Entity/white_tparent_v.glsl", (char*)SHADER_PATH"/Entity/white_tparent_f.glsl");
    progress_bar = Shader::read_file((char*)SHADER_PATH"/Entity/ProgressBar/TexturedProgress_vert.glsl",
        (char*)SHADER_PATH"/Entity/ProgressBar/TexturedProgress_frag.glsl");
    rain_fire = Shader::read_file((char*)SHADER_PATH"/Entity/Rain/vertex.glsl", (char*)SHADER_PATH"/Entity/Rain/fragment.glsl");
    atom = Shader::read_file((char*)SHADER_PATH"/Entity/Atom/vertex.glsl", (char*)SHADER_PATH"/Entity/Atom/frag.glsl");
    sphere_explosion = Shader::read_file((char*)SHADER_PATH"/Entity/SphereExplosion/vertex.glsl", (char*)SHADER_PATH"/Entity/SphereExplosion/frag.glsl");
    metal = Shader::read_file((char*)SHADER_PATH"/Entity/Metal/vertex.glsl", (char*)SHADER_PATH"/Entity/Metal/frag.glsl");
    plastic = Shader::read_file((char*)SHADER_PATH"/Entity/Plastic/vertex.glsl", (char*)SHADER_PATH"/Entity/Plastic/frag.glsl");
    low_health = Shader::read_file((char*)SHADER_PATH"/LowHealth/vertex.glsl", (char*)SHADER_PATH"/LowHealth/frag.glsl");

}


void LoadedShaders::create_procedural()
{
    const char *vertex = \
    "#version 130\n"
    "in vec3 vertex;\n"
    "in vec3 normal;\n"
    "in vec3 color;\n"
    "in vec2 uv;\n"
    "uniform mat4 world_mat;\n"
    "uniform mat4 view_mat;\n"
    "uniform mat4 projection_mat;\n"
    "uniform mat4 projection_2d;\n"
    "out vec4 color_interp;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = projection_mat * view_mat * world_mat * vec4(vertex, 1.0);\n"
    "    color_interp = vec4(color, 1.0);\n"
    "}\n";

    const char *fragment = \
    "#version 130\n"
    "in vec4 color_interp;\n"
    "void main()\n" 
    "{\n"
    "    gl_FragColor = color_interp;\n"
    "}\n";

    procedural = new Shader((char*)vertex, (char*)fragment);
}

void LoadedShaders::create_textured()
{
    char *vertex = (char*)\
    "#version 130\n"
    "in vec3 vertex;\n"
    "in vec3 normal;\n"
    "in vec3 color;\n"
    "in vec2 uv;\n"
    "uniform mat4 world_mat;\n"
    "uniform mat4 view_mat;\n"
    "uniform mat4 projection_mat;\n"
    "uniform mat4 normal_mat;\n"
    "out vec3 position_interp;\n"
    "out vec3 normal_interp;\n"
    "out vec4 color_interp;\n"
    "out vec2 uv_interp;\n"
    "out vec3 light_pos;\n"
    "uniform vec3 light_position = vec3(-0.5, -0.5, 1.5);\n"
    "void main()\n"
    "{\n"
    "    gl_Position = projection_mat * view_mat * world_mat * vec4(vertex, 1.0);\n"

    "    position_interp = vec3(view_mat * world_mat * vec4(vertex, 1.0));\n"
        
    "    normal_interp = vec3(normal_mat * vec4(normal, 0.0));\n"

    "    color_interp = vec4(color, 1.0);\n"

    "    uv_interp = uv;\n"

    "    light_pos = vec3(view_mat * vec4(light_position, 1.0));\n"
    "}\n";

    char *fragment = (char*)\
    "#version 130\n"
    "in vec3 position_interp;\n"
    "in vec3 normal_interp;\n"
    "in vec4 color_interp;\n"
    "in vec2 uv_interp;\n"
    "in vec3 light_pos;\n"
    "uniform sampler2D texture_map;\n"
    "void main() \n"
    "{\n"
    "    vec4 pixel = texture(texture_map, uv_interp);\n"
    "    gl_FragColor = pixel;\n"
    "}\n";
    textured = new Shader(vertex, fragment);
}

void LoadedShaders::create_label()
{
    char *vertex = (char*)\
    "#version 330 core\n"
    "in vec3 vertex;\n"
    "in vec3 normal;\n"
    "in vec3 color;\n"
    "in vec2 uv;\n"
    "uniform mat4 world_mat;\n"
    "uniform mat4 view_mat;\n"
    "uniform mat4 projection_mat;\n"
    "uniform mat4 normal_mat;\n"
    "uniform mat4 projection_2d;\n"
    "out vec4 color_interp;\n"
    "out vec2 uv_interp;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = projection_2d * world_mat * vec4(vertex, 1.0);\n"    
    "    color_interp = vec4(color, 1.0);\n"
    "    uv_interp = uv;\n"
    "}\n";

    char *fragment = (char*)\
    "#version 330 core\n"
    "uniform float xs[100];\n"
    "uniform float ys[100];\n"
    "uniform float length_of_text;\n"
    "uniform sampler2D texture_map;\n"
    "uniform vec3 background;\n"
    "uniform vec3 text_color;\n"
    "in vec4 color_interp;\n"
    "in vec2 uv_interp;\n"
    "void main() \n"
    "{\n"
    "    float p = uv_interp.x * length_of_text;\n"
    "    float remaining = mod(p, 1.0);\n"
    "    int index = int(p);\n"
    "    vec2 pos = vec2(xs[index] + (remaining / 25), ys[index] + ((1 - uv_interp.y) / 5.0));\n"
    "    vec4 pixel = texture(texture_map, pos);\n"
    "    float r = 0.0;\n"
    "    float g = 0.0;\n"
    "    float b = 0.0;\n"
    "    float a = 1.0;\n"
    "    if (pixel.r > 0.45)\n"
    "    {\n"
    "        a = 0.0;\n"
    "        r = background.r;\n"
    "        g = background.g;\n"
    "        b = background.b;\n"
    "    }\n"
    "    else\n"
    "    {\n"
    "        r = text_color.r;\n"
    "        g = text_color.g;\n"
    "        b = text_color.b;\n"
    "    }\n"
    "    gl_FragColor = vec4(r,g,b,a);\n"
    "}\n";
    label = new Shader(vertex, fragment);
}
void LoadedShaders::create_colored()
{
    const char *vertex = \
    "#version 130\n"
    "in vec3 vertex;\n"
    "in vec3 normal;\n"
    "in vec3 color;\n"
    "in vec2 uv;\n"
    "uniform mat4 world_mat;\n"
    "uniform mat4 view_mat;\n"
    "uniform mat4 projection_mat;\n"
    "uniform mat4 projection_2d;\n"
    "out vec4 color_interp;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = projection_mat * view_mat * world_mat * vec4(vertex, 1.0);\n"
    "    color_interp = vec4(color, 1.0);\n"
    "}\n";

    const char *fragment = \
    "#version 130\n"
    "in vec4 color_interp;\n"
    "uniform vec4 uni_color;"
    "void main()\n" 
    "{\n"
    "    gl_FragColor = uni_color;\n"
    "}\n";

    colored = new Shader((char*)vertex, (char*)fragment);
}


Shader *LoadedShaders::PROCEDURAL() const
{
    return procedural;
}

Shader *LoadedShaders::TEXTURED() const
{
    return textured;
}

Shader * LoadedShaders::LABEL() const
{
    return label;
}

Shader *LoadedShaders::COLORED() const
{
    return colored;
}

Shader *LoadedShaders::WHITE_TPARENT() const
{
    return white_tparent;
}
Shader *LoadedShaders::PROGRESS_BAR() const
{
    return progress_bar;
}

Shader *LoadedShaders::RAIN_FIRE() const
{
    return rain_fire;
}

Shader *LoadedShaders::ATOM() const
{
    return atom;
}

Shader *LoadedShaders::SPHERE_EXPLOSION() const
{
    return sphere_explosion;
}

Shader *LoadedShaders::METAL() const
{
    return metal;
}

Shader *LoadedShaders::PLASTIC() const
{
    return plastic;
}

Shader *LoadedShaders::LOW_HEALTH() const
{
    return low_health;
}

LoadedShaders::~LoadedShaders()
{
    delete procedural;
    delete textured;
    delete label;
    delete colored;
    delete white_tparent;
    delete progress_bar;
    delete rain_fire;
    delete atom;
    delete sphere_explosion;
    delete metal;
    delete plastic;
    delete low_health;
}