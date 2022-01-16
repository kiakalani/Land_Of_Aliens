#ifndef _SHADER_H_
#define _SHADER_H_
#include <stdint.h>
#include "../includes.hxx"

/// <h2> Author: Kia Kalani </h2>
/// <strong> Student ID: 101145220 </strong>
/// <summary>
/// <code>Shader</code> class represents the shader of the program.
/// It can be either created from files or strings.
/// Handling components on the shader side makes the code more readable
/// compared to the code provided in the examples.
/// </summary>
/// <strong> Last revised: Thursday, November 18th, 2021 </strong>
class Shader
{
    uint32_t program;

    public:
    Shader(char*, char*, char* = (char*)0);
    ~Shader();
    // Starts using the shader
    void invoke() const;
    // Called when work with the shader is done
    void end_use() const;

    // Sends the uniform int. It is mainly used for the texture
    void set_int(char*, const int&) const;

    // Sending other uniform variables to the shader program
    void set_uniform_float(char*, const float&) const;
    void set_uniform_vec2(char*, const glm::vec2&) const;
    void set_uniform_vec3(char*, const glm::vec3&) const;
    void set_uniform_vec4(char*, const glm::vec4&) const;
    void set_uniform_mat4(char*, const glm::mat4&) const;

    // Setting the attributes from the geometry
    void set_attribute(char *name, uint8_t attribute_size, uint8_t position, uint8_t total) const;
    // Creates a shader by reading a file.
    static Shader *read_file(char *vertex_path, char *fragment_path, char *geom_path=(char*)0);
};

#endif