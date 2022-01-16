#ifndef _CAMERA_HH_
#define _CAMERA_HH_
#include "../includes.hxx"
class Entity;
/// <h2> Author: Kia Kalani </h2>
/// <strong> Student ID: 101145220 </strong>
/// <summary>
/// The camera class.
/// This class represents the camera of the game. It has both
/// 2D and 3D projections within itself.
/// </summary>
/// <strong> Last Revised: Thursday, November 18th, 2021 </strong>
class Camera
{
    private:
    // Camera components
    float far_clip, near_clip, field_of_view;
    glm::vec3 position, forward, side;
    glm::mat4 view, projection, projection_2d;
    glm::quat orienation;
    glm::vec3 rotation_addition;

    // Speed for translation and rotation. This is done for making these tasks more smooth.
    float translation_fact;
    float up_fact;
    float left_fact;

    float pitch_fact;
    float yaw_fact;
    float roll_fact;

    Entity *to_follow;

    public:
    Camera(const glm::vec3& = glm::vec3(0.5f, 0.5f, -2.0f), 
    const glm::vec3& = glm::vec3(0.0f, 0.0f, 0.0f), 
    const glm::vec3& = glm::vec3(0.0f, 1.0f, 0.0f));

    void translate(const glm::vec3&);
    void rotate(const glm::quat&); 

    void follow_entity(Entity*);

    const Entity*& get_to_follow();
    // Relative unit vectors representing different axis
    glm::vec3 get_forward() const;
    glm::vec3 get_side() const;
    glm::vec3 get_up() const;

    // Getters of the matrices that are sent to the shader
    const glm::mat4 &get_projection_mat();
    const glm::mat4 &get_view_mat();
    const glm::mat4 &get_2d_proj_mat();
    const glm::vec3 &get_position();
    const glm::quat &get_orientation();

    void set_position(const glm::vec3&);

    void pitch(float);
    void yaw(float);
    void roll(float);

    // Setting the translation and rotation speeds
    void set_forward_speed(const float&);
    void set_side_speed(const float&);
    void set_up_speed(const float&);

    void set_pitch_speed(const float&);
    void set_yaw_speed(const float&);
    void set_roll_speed(const float&);
    void set_orientation(const glm::quat&);
    void set_forward(const glm::vec3&);

    void set_rotation_addition(const glm::vec3&);

    const glm::vec3 &get_rotation_addition();

    void update();

    void set_projection(uint16_t, uint16_t);

    void reset_camera(); 
};


#endif