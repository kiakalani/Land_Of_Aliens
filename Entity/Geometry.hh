#ifndef _GEOMETRY_HH_
#define _GEOMETRY_HH_
#include <stdint.h>
#include "../includes.hxx"
#include "../Shader/Shader.hh"

/// <h2> Author: Kia Kalani </h2>
/// <strong> Student ID: 101145220 </strong>
/// <summary>
/// <code>Geometry</code> class is the base class
/// for all of the shapes within the game.
/// </summary>
/// <strong> Last Revised: Thursday, November 18th, 2021 </strong>
class Geometry
{
    private:
    uint32_t vbo, ebo;
    uint64_t size;


    protected:
    // Loads the vertex buffer
    void load_vbo(float*, uint64_t) const;
    // Loads the faces
    void load_ebo(uint32_t*, uint64_t) const;
    void set_size(const uint64_t);

    public:
    Geometry();
    virtual ~Geometry();
    // Sending the attributes of the geometry to the program
    // from the shader to draw
    void render(Shader*) const;
    // Returns the size of faces.
    uint64_t get_size() const;

    void choose() const;
};

#endif