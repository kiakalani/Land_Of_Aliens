#ifndef _LABEL_HH_
#define _LABEL_HH_
#include "Entity.hh"
/// <h2> Author: Kia Kalani </h2>
/// <strong> Student ID: 101145220 </strong>
/// <summary>
/// <code>Label</code> class is responsible for showing text
/// in 2D space as a sprite. This is made possible with the 
/// alphabets texture located <a href="../Textures/alphabets.png".
/// Of course the quality of the text is fairly low but that is not
/// the point of using this class. For better quality, we could use a
/// better quality image as well. <br>
/// <strong> Note: </strong>
/// There is a word limit on this class and it is 100.<br>
/// <strong>Important:</strong> For further information about the shader
/// that is being used with this class please refer to <a href="../Shaders/Entity/Label">
/// this directory </a>
/// </summary>
/// <strong> Last Revised: Friday, November 19th, 2021 </strong>
class Label: public Entity
{
    private:
    char text[100];
    glm::vec3 text_color;
    glm::vec3 bg_color;

    public:
    Label();

    void render(const glm::mat4&, const glm::mat4&, const glm::mat4& = glm::mat4(1.0f)) const;

    // Changes the text
    void set_text(char*);

    // Sets the text color
    void set_text_color(uint8_t, uint8_t, uint8_t);

    // Sets the background color of the label
    void set_background_color(uint8_t, uint8_t, uint8_t);

    bool collided_mouse() const;
   
};
#endif
