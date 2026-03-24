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
        : m_rotation(1.0f)
    {

    }

    PT_FORCE_INLINE const glm::mat4 GetModel() const
    {
        return glm::translate(glm::mat4(1.0f), m_position) * m_rotation;
    }

    PT_FORCE_INLINE void AddOffsetLocation(const glm::vec3& offsetLocation)
    {
        m_position += offsetLocation;
    }

    PT_FORCE_INLINE void SetLocation(const glm::vec3& location)
    {
        m_position = location;
    }

    PT_FORCE_INLINE glm::vec3 GetLocation()
    {
        return m_position;
    }

    PT_FORCE_INLINE void AddOffsetRotation(const glm::vec3& axis, float angle)
    {
        m_rotation = glm::rotate(m_rotation, angle, axis);
    }

    PT_FORCE_INLINE void SetRotation(const glm::vec3& axis, float angle)
    {
        m_rotation = glm::rotate(glm::mat4(1.0f), angle, axis);
    }

private:
    glm::vec3 m_position;
    glm::mat4 m_rotation;
};

}
