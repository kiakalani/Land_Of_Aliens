#include "Shader.hh"
#include "../includes.hxx"
#include <stdio.h>
Shader::Shader(char *vert, char *frag, char *geom)
{
    uint32_t vert_sh = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert_sh, 1, &vert, (int*)0);
    glCompileShader(vert_sh);

    int success = 0;
    char *log = new char[10000];
    glGetShaderiv(vert_sh, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vert_sh, 10000, NULL, log);
        printf("Error compiling vertex shader:\n%s\n", log);
    }

    uint32_t frag_sh = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag_sh, 1, &frag, (int*)0);
    glCompileShader(frag_sh);

    glGetShaderiv(frag_sh, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(frag_sh, 10000, NULL, log);
        printf("Error compiling the fragment shader:\n%s\n", log);
    }

    uint32_t geom_sh = 0;
    if (geom)
    {
        geom_sh = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geom_sh, 1, &geom, (int*)0); 
        glGetShaderiv(geom_sh, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(geom_sh, 10000, NULL, log);
            printf("Error compiling the geometry shader:\n%s\n", log);
        }
    }
    

    program = glCreateProgram();
    glAttachShader(program, vert_sh);
    if (geom) glAttachShader(program, geom_sh);
    glAttachShader(program, frag_sh);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 10000, NULL, log);
        printf("Error linking the shaders:\n%s\n", log);
    }
    glDeleteShader(frag_sh);
    glDeleteShader(vert_sh);
    if (geom) glDeleteShader(geom_sh);
    delete[] log;
}

Shader::~Shader()
{
    glDeleteProgram(program);
}

void Shader::invoke() const
{
    glUseProgram(program);
}

void Shader::set_uniform_float(char *name, const float &f) const
{
    int loc = glGetUniformLocation(program, name);
    glUniform1f(loc, f);
}

void Shader::set_uniform_vec2(char *name, const glm::vec2 &v) const
{
    int loc = glGetUniformLocation(program, name);
    glUniform2fv(loc, 1, &v[0]);

}

void Shader::set_uniform_vec3(char *name, const glm::vec3 &v) const
{
    int loc = glGetUniformLocation(program, name);
    glUniform3fv(loc, 1, &v[0]);
}

void Shader::set_uniform_vec4(char *name, const glm::vec4 &v) const
{
    int loc = glGetUniformLocation(program, name);
    glUniform4fv(loc, 1, &v[0]);
}

void Shader::set_uniform_mat4(char *name, const glm::mat4 &m) const
{
    int loc = glGetUniformLocation(program, name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(m));
}

void Shader::end_use() const
{
    glUseProgram(0);
}

void Shader::set_attribute(char *name, uint8_t size, uint8_t pos, uint8_t total) const
{
    int attribute = glGetAttribLocation(program, name);
    glVertexAttribPointer(attribute, size, GL_FLOAT, GL_FALSE, total * sizeof(float), (void*)(pos * sizeof(float)));
    glEnableVertexAttribArray(attribute);
}

void Shader::set_int(char *name, const int &i) const
{
    int loc = glGetUniformLocation(program, name);
    glUniform1i(loc, i);
}

Shader *Shader::read_file(char *vert_sh, char *frag_sh, char *geom_sh)
{
    FILE *f = fopen(vert_sh, "r");
    if (!f)
    {
        printf("Error reading the vertex shader from file\nPath: %s\n", vert_sh);
        return (Shader*)0;
    }
    char cur_comp = 0;
    uint32_t count_vert_shader = 0, vert_shader_n = 0;
    char *vert_shader = new char[vert_shader_n = 1];
    while ((cur_comp = (char)fgetc(f)) != EOF)
    {
        if (count_vert_shader + 1 >= vert_shader_n)
        {
            char *temp = new char[vert_shader_n *= 2];
            for (uint32_t i = 0; i < count_vert_shader; ++i)
                temp[i] = vert_shader[i];
            char *del = vert_shader;
            vert_shader = temp;
            delete[] del;
        }
        vert_shader[count_vert_shader++] = cur_comp;
        vert_shader[count_vert_shader] = 0;
    }

    fclose(f);

    FILE *ff = fopen(frag_sh, "r");
    if (!ff)
    {
        printf("Error reading the fragment shader from file\nPath: %s\n", frag_sh);
        delete[] vert_shader;
        return (Shader*)0;
    }

    uint32_t count_frag_shader = 0, frag_shader_n = 0; 
    char *frag_shader = new char[frag_shader_n = 1];
    while ((cur_comp = (char)fgetc(ff)) != EOF)
    {
        if (count_frag_shader + 1 >= frag_shader_n)
        {
            char *temp = new char[frag_shader_n *= 2];
            for (uint32_t i = 0; i < count_frag_shader; ++i)
                temp[i] = frag_shader[i];
            char *del = frag_shader;
            frag_shader = temp;
            delete[] del;
        }
        frag_shader[count_frag_shader++] = cur_comp;
        frag_shader[count_frag_shader] = 0;
    }
    char *geom_shader = NULL;
    if (geom_sh)
    {
        FILE *file = fopen(geom_sh, "r");
        if (!file)
        {
            printf("Error reading the geometry shader from file\nPath: %s\n", geom_sh);
            delete[] vert_sh;
            delete[] frag_sh;
            return (Shader*)0;
        }
        uint32_t count_geom = 0, geom_n;
        geom_shader = new char[geom_n = 2];
        while ((cur_comp = (char)fgetc(file)) != EOF)
        {
            if (count_geom + 1 >= geom_n) {
                char *temp = new char[geom_n *= 2];
                for (uint32_t i = 0; i < count_geom; ++i)
                temp[i] = geom_shader[i];
                char *del = geom_shader;
                geom_shader = temp;
                delete[] del;
            }
            geom_shader[count_geom++] = cur_comp;
            geom_shader[count_geom] = 0;
        }
        
        fclose(file);
    }

    Shader *shader = new Shader(vert_shader, frag_shader, geom_shader);
    delete[] vert_shader;
    delete[] frag_shader;
    if (geom_shader) delete[] geom_shader;

    fclose(ff);

    return shader;
}