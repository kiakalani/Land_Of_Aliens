#version 330 core

in vec3 color_interp;
in float alpha;
void main()
{
    gl_FragColor = vec4(color_interp, alpha);
}
