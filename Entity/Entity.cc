#include "Entity.hh"
#include "../Texture/Texture.hh"
#include <stdio.h>
Entity::Entity(Geometry *geom, Shader *shad, Texture *tex):
    shape(geom), shader(shad), texture(tex), position(0.0f, 0.0f, 0.0f),
    obj_scale(1.0f, 1.0f, 1.0f), orientation(glm::quat()), orbit(glm::mat4(1.0f)),
    removed(false), count_dups(1), transparent(0), parent(glm::mat4(1.0f)), terrained(0), trans_speed(0),
    uni_color(0.0f), collision_width(-1), collision_height(-1), collision_depth(-1), health(1.0f), team(NEUTRAL)
{}



glm::vec3 Entity::get_position() const
{
    return position;
}

glm::mat4 Entity::get_orbit() const
{
    return orbit;
}

bool Entity::is_terrained() const
{
    return terrained;
}

void Entity::set_terrained(const bool &b)
{
    terrained = b;
}

glm::vec3 Entity::get_scale() const
{
    return obj_scale;
}

glm::quat Entity::get_orientation() const
{
    return orientation;
}

void Entity::translate(const glm::vec3 &v)
{
    position += v;
}

void Entity::rotate(const glm::quat &q)
{
    orientation = glm::normalize(orientation * q);
}

void Entity::scale(const glm::vec3 &s)
{
    obj_scale *= s;
}

void Entity::set_translate(const glm::vec3 &t)
{
    position = t;
}

void Entity::set_count_duplicates(const uint32_t &c)
{
    count_dups = c;
}

void Entity::set_orientation(const glm::quat &q)
{
    orientation = q;
}

void Entity::set_scale(const glm::vec3 &s)
{
    obj_scale = s;
}

void Entity::set_orbit(const glm::mat4 &m)
{
    orbit = m;
}

void Entity::set_uni_color(const glm::vec4 &c)
{
    uni_color = c;
}

void Entity::setup_render_elems(const glm::mat4 &view, const glm::mat4 &projection, const glm::mat4 &projection_2d) const
{
    shader->invoke();
    glm::mat4 g_scale = glm::scale(glm::mat4(1.0f), obj_scale);
    glm::mat4 g_rot = glm::mat4_cast(orientation);
    glm::mat4 g_trans = glm::translate(glm::mat4(1.0), position);
    glm::mat4 final_trans = parent * g_trans * orbit * g_rot * glm::inverse(orbit)  * g_scale;
    
    
    shader->set_uniform_mat4((char*)"world_mat", final_trans);
    shader->set_uniform_mat4((char*)"normal_mat", glm::transpose(glm::inverse(final_trans)));
    shader->set_uniform_mat4((char*)"view_mat", view);
    shader->set_uniform_mat4((char*)"projection_mat", projection);
    shader->set_uniform_mat4((char*)"projection_2d", projection_2d);
    shader->set_uniform_float((char*)"current_time", (float)glfwGetTime());
    shader->set_uniform_vec4((char*)"uni_color", uni_color);
    if (transparent)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    }
    
}
bool Entity::is_transparent() const
{
    return transparent;
}

void Entity::set_transparent(const bool &t)
{
    transparent = t;
}
void Entity::setup_render_draw() const
{
    shape->render(shader);
    
    
    if (texture)
    texture->render_texture(shader);
    
    if (count_dups == 1)
    {
        glDrawElements(GL_TRIANGLES, shape->get_size(), GL_UNSIGNED_INT, 0);
    }
    else
    {
        glDrawElementsInstanced(GL_TRIANGLES, shape->get_size(), GL_UNSIGNED_INT, 0, count_dups);
    }

    shader->end_use();
    texture->end_render();
    glDisable(GL_BLEND);
    // collision_shape.update(position[0], position[1]);
}

void Entity::render(const glm::mat4 &camera_view, const glm::mat4 &projection, const glm::mat4 &projection_2d) const
{
    setup_render_elems(camera_view, projection, projection_2d);
    // Over here any needed components for the shader can be passed
    setup_render_draw();
}

void Entity::remove()
{
    removed = true;
}

bool Entity::is_removed() const
{
    return removed;
}

void Entity::update()
{
    position += trans_speed;
}

void Entity::set_shader(const Shader *&s)
{
    shader = (Shader*)s;
}

void Entity::set_geometry(const Geometry *&g)
{
    shape = (Geometry*)g;
}

void Entity::set_texture(const Texture *&t)
{
    texture = (Texture*)t;
}

glm::mat4 Entity::calculate_world() const
{
    glm::mat4 g_scale = glm::scale(glm::mat4(1.0f), obj_scale);
    glm::mat4 g_rot = glm::mat4_cast(orientation);
    glm::mat4 g_trans = glm::translate(glm::mat4(1.0), position);
    glm::vec3 testorb(-0.4, 1.0, 0.0);
    glm::mat4 rotation = orbit * g_rot * glm::inverse(orbit);
    glm::mat4 final_trans =   parent  * g_trans  * rotation  * g_scale ;
    return final_trans;
}


void Entity::set_parent(const glm::mat4 &p)
{
    parent = p;
}

void Entity::handle_terrain_collision(const float &y, const float &gravity)
{
    return;
}

void Entity::set_translate_speed(const glm::vec3 &t)
{
    trans_speed += t;
}

const glm::vec3 &Entity::get_translate_speed()
{
    return trans_speed;
}


float Entity::get_collision_radius() const
{
    return 0.0f;
}

void Entity::set_collision_width(const float &w)
{
    collision_width = w;
}

void Entity::set_collision_height(const float &h)
{
    collision_height = h;
}

void Entity::set_collision_depth(const float &d)
{
    collision_depth = d;
}

bool Entity::collides(const Entity *&e) const
{
    float tmin_x = get_position()[0] + trans_speed[0] - collision_width * 0.5f;
    float tmin_y = get_position()[1] - collision_height * 0.5f;
    float tmin_z = get_position()[2] + trans_speed[2] - collision_depth * 0.5f;
    float tmax_x = get_position()[0] + trans_speed[0] + collision_width * 0.5f;
    float tmax_y = get_position()[1] + collision_height * 0.5f;
    float tmax_z = get_position()[2] + trans_speed[2] + collision_depth * 0.5f;

    float min_x = e->get_position()[0] + e->trans_speed[0] - e->collision_width * 0.5f;
    float min_y = e->get_position()[1] - e->collision_height * 0.5f;
    float min_z = e->get_position()[2] + e->trans_speed[2] - e->collision_depth * 0.5f;
    float max_x = e->get_position()[0] + e->trans_speed[0] + e->collision_width * 0.5f;
    float max_y = e->get_position()[1]  + e->collision_height * 0.5f;
    float max_z = e->get_position()[2] + e->trans_speed[2] + e->collision_depth * 0.5f;
    
    // Simple cubic collision but effective.
    return tmin_x <= max_x && tmax_x >= min_x && tmin_y <= max_y && tmax_y >= min_y
        && tmin_z <= max_z && tmax_z >= min_z;
}

void Entity::handle_collision(Entity *e)
{
    if (e->collision_width >= 0 && collision_height >=0 && collision_depth >= 0)
    {
        translate(glm::vec3(-get_translate_speed()[0], 0.0f, -get_translate_speed()[2]));
        set_translate_speed(-get_translate_speed());
    }
    
}


void Entity::handle_other(Entity *e)
{}

float Entity::get_health() const
{
    return health;
}


void Entity::take_damage(const float &d)
{
    health -= d;
}

EntityTeam Entity::get_entity_team() const
{
    return team;
}

void Entity::set_entity_team(const EntityTeam &e)
{
    team = e;
}

void Entity::set_texture(Texture *t)
{
    texture = t;
}