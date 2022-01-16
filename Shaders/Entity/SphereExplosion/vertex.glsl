#version 330 core

in vec3 vertex;
in vec3 normal;
in vec3 color;
in vec2 uv;

uniform mat4 world_mat;
uniform mat4 view_mat;
uniform mat4 projection_mat;
uniform mat4 projection_2d;
uniform float anglex[200];
uniform float angley[200];
uniform float anglez[200];
uniform float current_time;
out vec3 color_interp;
out float alpha;
void main()
{
    float theta = 2* 3.14 * anglex[gl_InstanceID];
    float phi = acos(2 * angley[gl_InstanceID] - 1);
    float r = anglez[gl_InstanceID];
    color_interp = color;
    float magnitude = 15.0;
    vec4 final_vert = vec4(vertex, 1.0);
    float multiple = mod(current_time * 5, magnitude);
    final_vert.x -= r * cos(theta) * sin(phi) * multiple;
    final_vert.y -= r * sin(theta) * sin(phi) * multiple;
    final_vert.z -= r * cos(phi);
    alpha =1.0 - multiple / magnitude;
    float scale = alpha;
    // if (scale < 0.5) scale = 0.5;
    mat4 scale_mat;
    scale_mat[0] = vec4(scale, 0.0, 0.0, 0.0);
    scale_mat[1] = vec4(0.0, scale, 0.0, 0.0);
    scale_mat[2] = vec4(0.0, 0.0, scale, 0.0);
    scale_mat[3] = vec4(0.0, 0.0, 0.0, 1.0);
    gl_Position = projection_mat * view_mat * world_mat * scale_mat * final_vert;
}