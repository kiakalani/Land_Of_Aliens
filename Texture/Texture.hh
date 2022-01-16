#ifndef _TEXTURE_HH_
#define _TEXTURE_HH_
#include <stdint.h>
class Shader;
class GameWorld;
/// <h2> Author: Kia Kalani </h2>
/// <strong> Student ID: 101145220 </strong>
/// <summary>
/// <code>Texture</code> class creates a texture instance
/// that would be used for rendering textures on the 
/// <code>Geometry</code> instances within each entity.
/// </summary>
/// <strong> Last Revised: Thursday, November 18th, 2021 </strong>
class Texture
{
    private:
    uint32_t texture;
    uint32_t fbo, dbo;
    GameWorld *window;
    public:
    Texture(char* = (char*)0);

    // Texture(GameWorld*&);
    ~Texture();
    // Rendering the texture on the shader
    void render_texture(Shader*, char* = (char*)"texture_map", int = 0) const;

    void render_scene_to_texture() const;
    void end_render_scene_to_texture() const;
    // Stop using the texture.
    void end_render() const;

    void render_window() const;
};
#endif