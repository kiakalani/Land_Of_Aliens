#include "Geometry.hh"
#include <stdio.h>
Geometry::Geometry()
{
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    size = 0;
}

Geometry::~Geometry()
{
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

void Geometry::render(Shader *sh) const
{
    choose();
    sh->set_attribute((char*)"vertex", 3, 0, 11);
    sh->set_attribute((char*)"normal", 3, 3, 11);
    sh->set_attribute((char*)"color", 3, 6, 11);
    sh->set_attribute((char*)"uv", 2, 9, 11);
}

void Geometry::load_vbo(float *verts, uint64_t count_verts) const
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, count_verts * sizeof(float), verts, GL_STATIC_DRAW);
}

void Geometry::load_ebo(uint32_t *faces, uint64_t count_faces) const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count_faces * sizeof(uint32_t), faces, GL_STATIC_DRAW);
}

void Geometry::set_size(const uint64_t s)
{
    size = s;
}

uint64_t Geometry::get_size() const
{
    return size;
}

void Geometry::choose() const
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}