#include "Texture.hh"
#include <SOIL/SOIL.h>
#include "../includes.hxx"
#include <stdio.h>
#include "../Shader/Shader.hh"
#include "../World/GameWorld.hh"
#include "../Display/GameDisplay.hh"
Texture::Texture(char *path)
{
    if (path)
    {
        texture = SOIL_load_OGL_texture(path, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0);
        if (!texture)
        {
            printf("Error loading the texture %s\n", path);
        }
    }
    else
    {
        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, GameDisplay::get_width(), GameDisplay::get_height(), 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glGenRenderbuffers(1, &dbo);
        glBindRenderbuffer(GL_RENDERBUFFER, dbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, GameDisplay::get_width(), GameDisplay::get_height());
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, dbo);
        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);
        uint32_t dbuf = GL_COLOR_ATTACHMENT0;
        glDrawBuffers(1, &dbuf);
    }
    
}

void Texture::render_scene_to_texture() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glViewport(0, 0, GameDisplay::get_width(), GameDisplay::get_height());
}

Texture::~Texture()
{
    glDeleteTextures(1, &texture);
    if (fbo) glDeleteFramebuffers(1, &fbo);
    if (dbo) glDeleteRenderbuffers(1, &dbo);
}

void Texture::render_texture(Shader *shader, char *name, int pos) const
{
    shader->set_int(name, pos);
    glActiveTexture(GL_TEXTURE0 + pos);
    glBindTexture(GL_TEXTURE_2D, texture);

    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T , GL_REPEAT);
}

void Texture::end_render() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::end_render_scene_to_texture() const
{
    int32_t viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);

}