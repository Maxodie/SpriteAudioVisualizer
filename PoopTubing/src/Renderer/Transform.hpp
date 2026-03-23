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
        : m_model(1.0f)
    {

    }

    PT_FORCE_INLINE const glm::mat4& GetModel() const
    {
        return m_model;
    }

    PT_FORCE_INLINE void AddOffsetLocation(const glm::vec3& offsetLocation)
    {
        m_model = glm::translate(m_model, offsetLocation);
    }

    PT_FORCE_INLINE void AddOffsetRotation(const glm::vec3& axis, float angle)
    {
        m_model = glm::rotate(m_model, angle, axis);
    }

private:
    glm::mat4 m_model;
};

}
