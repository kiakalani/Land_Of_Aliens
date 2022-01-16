#version 330 core


in vec2 uv_interp;
in vec3 color_interp; // Not needed
in vec4 point_pos;
in float id;
in float multiple;
uniform float xmult[2000];
uniform float current_time;
uniform sampler2D texture_map;
void main()
{
    gl_FragColor = texture(texture_map, uv_interp);
    if (id == 0.0) {}
    else { // other instances
        gl_FragColor.a = uv_interp.x - 0.5 * uv_interp.y + 0.5;
    }
    
}