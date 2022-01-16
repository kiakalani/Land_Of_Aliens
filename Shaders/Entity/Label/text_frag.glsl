#version 330 core


uniform float xs[100];
uniform float ys[100];

uniform float length_of_text;

uniform sampler2D texture_map;
uniform vec3 background;
uniform vec3 text_color;

in vec4 color_interp;
in vec2 uv_interp;


void main() 
{
    // Retrieve texture value
    float p = uv_interp.x * length_of_text;

    float remaining = mod(p, 1.0);

    
    int index = int(p);

    vec2 pos = vec2(xs[index] + (remaining / 25), ys[index] + ((1 - uv_interp.y) / 5.0));


    vec4 pixel = texture(texture_map, pos);

    float r = 0.0;
    float g = 0.0;
    float b = 0.0;
    float a = 1.0;

    if (pixel.r > 0.45)
    {
        a = 0.0;
        r = background.r;
        g = background.g;
        b = background.b;
    }
    else
    {
        r = text_color.r;
        g = text_color.g;
        b = text_color.b;
    }
    // Use texture in determining fragment colour
    gl_FragColor = vec4(r,g,b,a);
}