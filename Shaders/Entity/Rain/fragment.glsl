#version 330 core


uniform sampler2D texture_map;

in vec2 uv_interp;
in vec2 particles[20];

void main()
{
    vec4 pixel = vec4(0, 0, 0, 1);
    float alpha = 0.0;
    for (int i = 0; i < 20; i++)
    {
        float len = 0;
        if ((len = length(uv_interp - particles[i])) < 0.003)
        {
            alpha = 100.0 * len;
            pixel.r = 50.0 * len;
            pixel.g = 0.8;
            // pixel.b = pixel.y;
        }
        // if (abs(uv_interp.x - particles[i].x) <= 0.01)
        // {
        //     if (abs(uv_interp.y - particles[i].y) <= 0.01)
        //     {
                
        //     }
        // }
    }
    // vec4 pixel = texture(texture_map, uv_interp);
    // float alpha = 1.0;
    // if (pixel.r > 0.8 && pixel.g > 0.8 && pixel.b > 0.8)
    // {
    //     alpha = 0.0;
    // }
    gl_FragColor = vec4(pixel.r, pixel.g, pixel.b, alpha);
}