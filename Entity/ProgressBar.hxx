#ifndef _PROGRESS_BAR_HXX_
#define _PROGRESS_BAR_HXX_
#include "Entity.hh"

/// <h2> Author: Kia Kalani</h2>
/// <strong> Student ID: 101145220 </strong>
/// <summary>
/// <code>ProgressBar</code> class creates a progress
/// bar and makes the progress percentage visible.
/// Note that doing so is of course handled in the shader
/// related to this class. For now, there is only a shader
/// with texture that is functional with this code and there
/// would be no need for anything else but textured progress bars
/// anyway.
/// <strong>Note:</strong> For further information about the shader
/// that corresponds with this class, refer to <a href="../Shaders/Entity/ProgressBar">
/// the directory of the shader. </a>
/// </summary>
/// <strong> Last Revised: Friday November 19th, 2021 </strong>
class ProgressBar: public Entity
{
    private:
    float progress;
    public:

    ProgressBar(Texture* = (Texture*)0);

    // Sets the value for progression. We can put many things such as fuel, health etc.
    void set_progress(float percentage);

    void render(const glm::mat4&, const glm::mat4&, const glm::mat4&) const;

    float get_progress() const;

};
#endif
