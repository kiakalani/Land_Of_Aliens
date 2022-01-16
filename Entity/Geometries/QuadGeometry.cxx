#include "QuadGeometry.hxx"

QuadGeometry::QuadGeometry(): Geometry()
{
    // Definition of the wall
    // The wall is simply a quad formed with two triangles
    GLfloat vertex[] = {
        // Position, normal, color, texture coordinates
        // Here, color stores the tangent of the vertex
        -1.0, -1.0, 0.0,  0.0, 0.0,  1.0,  1.0, 0.0, 0.0,  0.0, 0.0,
        -1.0,  1.0, 0.0,  0.0, 0.0,  1.0,  1.0, 0.0, 0.0,  0.0, 1.0,
         1.0,  1.0, 0.0,  0.0, 0.0,  1.0,  1.0, 0.0, 0.0,  1.0, 1.0,
         1.0, -1.0, 0.0,  0.0, 0.0,  1.0,  1.0, 0.0, 0.0,  1.0, 0.0};
    GLuint face[] = {0, 2, 1,
                     0, 3, 2};

    // Create OpenGL buffers and copy data
    load_vbo(vertex, sizeof(vertex) / sizeof(float));
    // GLuint vbo, ebo;
    load_ebo(face, 6);
    set_size(6);

    
}

QuadGeometry::~QuadGeometry()
{}