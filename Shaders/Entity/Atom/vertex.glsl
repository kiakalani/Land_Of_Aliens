#version 330 core

in vec3 vertex;
in vec3 color;
in vec3 normal;
in vec2 uv;

uniform mat4 world_mat;
uniform mat4 view_mat;
uniform mat4 projection_mat;
uniform float current_time;
uniform float xmult[200];
uniform float ymult[200];
uniform float zmult[200];
uniform vec3 positions[10];
uniform vec3 scale;


out vec2 uv_interp;
out vec3 color_interp;
out vec4 point_pos;
out float id;
out float x_multiple;
void main() 
{      
    vec4 current_vertex = vec4(vertex, 1.0); 
    // sent to fragment
    id = float(gl_InstanceID);
    x_multiple = 1.0;

    if (gl_InstanceID != 0)
    { // calculating the position of the vertex of each instance

        x_multiple = xmult[gl_InstanceID];
        current_vertex += vec4(positions[gl_InstanceID], 1.0);
        current_vertex.x +=  ( 10 * cos(current_time  * xmult[gl_InstanceID])) * gl_InstanceID * 0.02;
        current_vertex.y += 10 * ( sin(current_time   * ymult[gl_InstanceID])) * gl_InstanceID * 0.02;
        current_vertex.z += 10 *  sin(current_time)  * zmult[gl_InstanceID] * gl_InstanceID * 0.02;
    }

    // sent to fragment
    point_pos = current_vertex;
    uv_interp = uv;
    color_interp = color;

    // for scaling
    mat4 multmat;
    multmat[0] = vec4(0.5, 0.0, 0.0, 0.0);
    multmat[1] = vec4(0.0, 0.5, 0.0, 0.0);
    multmat[2] = vec4(0.0, 0.0, 0.5, 0.0);
    multmat[3] = vec4(0.0, 0.0, 0.0, 1.0);

    
    if (gl_InstanceID != 0) // the other circles
    gl_Position = projection_mat * view_mat * (world_mat * multmat) * current_vertex;
    else // the main circle
        gl_Position = projection_mat * view_mat * (world_mat) * current_vertex;
}