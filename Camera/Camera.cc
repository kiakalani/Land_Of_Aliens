#include "Camera.hh"
#include "../Entity/Entity.hh"
#include <stdio.h>
Camera::Camera(const glm::vec3 &pos, const glm::vec3 &look, const glm::vec3 &up_dir):
    position(pos), orienation(glm::quat()), translation_fact(0), pitch_fact(0), roll_fact(0), yaw_fact(0),
    left_fact(0), up_fact(0)
{
    forward = -glm::normalize(look - pos);
    side = glm::normalize(glm::cross(up_dir, forward));
    far_clip = 1000.0f;
    near_clip = 0.01f;
    field_of_view = 20.0f;
    projection_2d = glm::ortho(-50.0f, 50.0f, -50.0f, 50.0f, -1.0f, 1.0f);
    to_follow = (Entity*)0;
    rotation_addition = glm::vec3(0.0f);
    update();
    
}

const Entity *&Camera::get_to_follow()
{
    return (const Entity*&)to_follow;
}

void Camera::set_rotation_addition(const glm::vec3 &v)
{
    rotation_addition += v;
    update();
}

const glm::vec3 &Camera::get_rotation_addition()
{
    return rotation_addition;
}

void Camera::update()
{

    if (to_follow)
    {
        forward = -glm::normalize(to_follow->get_position() - get_position());

        side = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), forward));

        position = to_follow->get_position() + glm::vec3(0.0f, 15.0f, -100.0f);
        float len_diff = glm::length(position - to_follow->get_position());
        float xdiff = position[0] - to_follow->get_position()[0];
        float zdiff = position[2] - to_follow->get_position()[2];
        len_diff = glm::sqrt(xdiff * xdiff + zdiff * zdiff);
        position[0] -= glm::sin(rotation_addition[0]) * len_diff;
        position[2] -=  glm::cos(rotation_addition[2]) * len_diff - len_diff;
    }
    else
    {
        translate(get_forward() * translation_fact);
        translate(get_side() * left_fact);
        translate(get_up() * up_fact);
    }
    
    
    
    

    float unit_rot = glm::pi<float>() / 180.0f;
    pitch(pitch_fact* unit_rot);
    yaw(yaw_fact * unit_rot);
    roll(roll_fact * unit_rot);

    glm::vec3 fwd = orienation * forward;
    glm::vec3 sd = orienation * side;
    glm::vec3 up = glm::normalize(glm::cross(fwd, sd));
    view = glm::mat4(1.0f);
    for (uint8_t i = 0; i < 3; ++i)
    {
        view[i][0] = sd[i];
        view[i][1] = up[i];
        view[i][2] = fwd[i];
    }

    view *= glm::translate(glm::mat4(1.0f), -position);

}

void Camera::rotate(const glm::quat &q)
{
    orienation = glm::normalize(q * orienation);
}

void Camera::translate(const glm::vec3 &v)
{
    position += v;
}

void Camera::set_forward_speed(const float &speed)
{
    translation_fact = speed;
}

void Camera::set_side_speed(const float &speed)
{
    left_fact = speed;
}

void Camera::set_up_speed(const float &speed)
{
    up_fact = speed;
}

void Camera::set_pitch_speed(const float &speed)
{
    pitch_fact = speed;
}

void Camera::set_yaw_speed(const float &speed)
{
    yaw_fact = speed;
}

void Camera::set_roll_speed(const float &speed)
{
    roll_fact = speed;
}

glm::vec3 Camera::get_forward() const
{
    return -(orienation * forward);
}

void Camera::set_orientation(const glm::quat &q)
{
    orienation = glm::normalize(q);
}

void Camera::set_forward(const glm::vec3 &v)
{
    forward = glm::normalize(v);
}

glm::vec3 Camera::get_side() const
{
    return orienation * side;
}

const glm::quat &Camera::get_orientation()
{
    return orienation;
}

void Camera::pitch(float p)
{
    orienation = glm::angleAxis(p, get_side()) * orienation;
    orienation = glm::normalize(orienation);
}

void Camera::yaw(float y)
{
    orienation = glm::angleAxis(y, get_up()) * orienation;
    orienation = glm::normalize(orienation);
}

void Camera::roll(float r)
{
    orienation = glm::angleAxis(r, get_forward()) * orienation;
    orienation = glm::normalize(orienation);
}

glm::vec3 Camera::get_up() const
{
    return glm::normalize(glm::cross(get_forward(), get_side()));
}

const glm::mat4 &Camera::get_projection_mat()
{
    return projection;
}

const glm::mat4 &Camera::get_view_mat()
{
    return view;
}

void Camera::set_projection(uint16_t width, uint16_t height)
{
    float top = glm::tan((field_of_view / 2.0f) * (glm::pi<float>() / 180.0f)) * near_clip;
    float right = top * (float)width / (float)height;
    projection = glm::frustum(-right, right, -top, top, near_clip, far_clip);
}


const glm::mat4 &Camera::get_2d_proj_mat()
{
    return projection_2d;
}

const glm::vec3 &Camera::get_position()
{
    return position;
}

void Camera::set_position(const glm::vec3 &pos)
{
    position = pos;
}

void Camera::follow_entity(Entity *e)
{
    to_follow = e;
    if (!e)
    {
        
    } else {
        forward = -glm::normalize(e->get_position() - get_position());

        side = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), forward);
        orienation = glm::quat();
        position = glm::vec3(0.5f, 0.5f, -2.0f);
    }



}

void Camera::reset_camera()
{
    
}