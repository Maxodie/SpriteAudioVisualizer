#pragma once
#include "Core.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/glm.hpp"

namespace PT
{

class Transform
{
public:
    Transform()
        : m_translation(1.0f)
    {

    }

    PT_INLINE const glm::mat4& GetTranslation() const
    {
        return m_translation;
    }

    PT_INLINE void AddOffsetLocation(const glm::vec3 offsetLocation)
    {
        m_translation = glm::translate(m_translation, offsetLocation);
    }

private:
    glm::mat4 m_translation;
};

}
