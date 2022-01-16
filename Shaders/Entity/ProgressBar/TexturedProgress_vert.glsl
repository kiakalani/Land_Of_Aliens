#version 330 core

in vec3 vertex;
in vec3 normal;
in vec3 color;
in vec2 uv;

uniform mat4 world_mat;
uniform mat4 projection_2d;


out vec2 uv_interp;



void main()
{
    gl_Position = projection_2d * world_mat * vec4(vertex, 1.0);    


    uv_interp = vec2(uv.x, 1.0 - uv.y);
}