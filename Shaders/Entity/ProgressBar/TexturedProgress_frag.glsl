#version 330 core

uniform float progress;

uniform sampler2D texture_map;

in vec2 uv_interp;

void main()
{
    vec4 pixel = texture(texture_map, uv_interp);
    float alpha = 1.0;
    if (uv_interp.x > progress || (pixel.r > 0.8 && pixel.g > 0.8 && pixel.b > 0.8))
    {
        alpha = 0.0;
    }
    gl_FragColor = vec4(pixel.r, pixel.g, pixel.b, alpha);
}