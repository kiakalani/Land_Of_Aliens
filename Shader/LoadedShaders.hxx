#ifndef _LOADED_SHADERS_HXX_
#define _LOADED_SHADERS_HXX_
#include "Shader.hh"
class LoadedShaders // Avoiding external read and writes as much as possible
{
    private:
    Shader *procedural;
    Shader *textured;
    Shader *label;
    Shader *colored;
    Shader *white_tparent;
    Shader *progress_bar;
    Shader *rain_fire;
    Shader *atom;
    Shader *sphere_explosion;
    Shader *metal;
    Shader *plastic;
    Shader *low_health;

    void create_procedural();
    void create_textured();
    void create_label();
    void create_colored();

    public:
    Shader *PROCEDURAL() const;
    Shader *TEXTURED() const;
    Shader *LABEL() const;
    Shader *COLORED() const;
    Shader *WHITE_TPARENT() const;
    Shader *PROGRESS_BAR() const;
    Shader *RAIN_FIRE() const;
    Shader *ATOM() const;
    Shader *METAL() const;
    Shader *PLASTIC() const;


    Shader *SPHERE_EXPLOSION() const;

    Shader *LOW_HEALTH() const;

    LoadedShaders();
    ~LoadedShaders();
};
#endif
