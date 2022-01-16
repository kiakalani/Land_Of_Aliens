#version 330 core

in vec3 vertex;
in vec3 normal;
in vec3 color;
in vec2 uv;

uniform mat4 world_mat;
uniform mat4 projection_2d;


out vec2 uv_interp;

out vec2 particles[20];

uniform float current_time;
float maximum = 27644437;
float num = 1333.0;
float random()
{
    num = mod(num * maximum, maximum);
    return mod(num, 1.0);
}
void main()
{
    for (int i = 0; i < 20; ++i)
    {
        particles[i] = vec2(i / 20.0, (1.0 - mod(i / 20.0 + current_time * 5.0, 1.0)));
        
    }

    gl_Position = projection_2d * world_mat * vec4(vertex, 1.0);    

    
    uv_interp = vec2(uv.x, 1.0 - uv.y);
}