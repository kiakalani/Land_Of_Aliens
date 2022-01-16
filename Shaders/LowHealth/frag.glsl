#version 330 core
layout(location = 0) out vec3 color;
// Attributes passed from the vertex shader
in vec3 position_interp;
in vec3 normal_interp;
in vec4 color_interp;
in vec2 uv_interp;
in vec3 light_pos;

// Uniform (global) buffer
uniform sampler2D texture_map;
uniform float current_time;

void main() 
{
    // Retrieve texture value
    vec4 pixel = texture(texture_map, uv_interp);
    float count_pixel_summation = mod(current_time * 20, 20);

    if (count_pixel_summation > 10.0) count_pixel_summation = 20.0 - count_pixel_summation;
    int blur_pixels = int(count_pixel_summation) + 1;

    float r_avg = 0.0, g_avg = 0.0, b_avg = 0.0;
    
    for (int i = 0; i < blur_pixels; i++) {
        if (blur_pixels > 5)
        {
            vec4 pix = texture(texture_map, vec2(uv_interp.x + i * 0.001, uv_interp.y + i * 0.001));
            r_avg += pix.r;
            g_avg += pix.g;
            b_avg += pix.b;
        }
        else
        {
            vec4 pix = texture(texture_map, vec2(uv_interp.x - i * 0.001, uv_interp.y + i * 0.001));
            r_avg += pix.r;
            g_avg += pix.g;
            b_avg += pix.b;
        }
        
        
    }
    

    r_avg /= abs(blur_pixels);
    g_avg /= abs(blur_pixels);
    b_avg /= abs(blur_pixels);
    // Use texture in determining fragment colour
    gl_FragColor = vec4(r_avg, g_avg, b_avg, 1.0);
}