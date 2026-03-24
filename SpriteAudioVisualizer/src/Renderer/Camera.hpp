#pragma once
#include "Core.hpp"
#include "glm/glm.hpp"

namespace PT
{

class Camera
{
public:
    void Setup(float fov, float aspectRatio, float near, float far);

    PT_INLINE const glm::mat4& GetView()
    {
        return m_view;
    }

    PT_INLINE const glm::mat4& GetProjection()
    {
        return m_projection;
    }

private:
    glm::mat4 m_projection;

    glm::mat4 m_view;
};

}
