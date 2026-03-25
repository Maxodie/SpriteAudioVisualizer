#pragma once
#include "Core.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/scalar_constants.hpp"
#include "glm/gtc/quaternion.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtx/quaternion.hpp"

namespace PT
{

class Transform
{
public:
    Transform()
        : m_rotation(1.0f), m_scale(glm::scale(glm::mat4(1.0f), glm::vec3(3.f, 3.f, 3.f)))
    {

    }

    Transform(const glm::vec3& scale)
        : m_rotation(1.0f), m_scale(glm::scale(glm::mat4(1.0f), scale))
    {

    }

    PT_FORCE_INLINE const glm::mat4 GetModel() const
    {
        return glm::translate(glm::mat4(1.0f), m_position) * m_rotation * m_scale;
    }

    PT_FORCE_INLINE void AddOffsetLocation(const glm::vec3& offsetLocation)
    {
        m_position += offsetLocation;
    }

    PT_FORCE_INLINE void SetLocation(const glm::vec3& location)
    {
        m_position = location;
    }

    PT_FORCE_INLINE const glm::vec3& GetLocation()
    {
        return m_position;
    }

    PT_FORCE_INLINE glm::quat GetRotation() const
    {
        return glm::toQuat(m_rotation);
    }

    PT_FORCE_INLINE void AddOffsetRotation(const glm::vec3& axis, float angle)
    {
        m_rotation = glm::rotate(m_rotation, angle, axis);
    }

    PT_FORCE_INLINE void SetRotation(const glm::vec3& axis, float angle)
    {
        m_rotation = glm::rotate(glm::mat4(1.0f), angle, axis);
    }

    PT_FORCE_INLINE void SetRotation(const glm::quat& rotation)
    {
        m_rotation = glm::toMat4(rotation);
    }

    PT_FORCE_INLINE static glm::quat MakeQuatFromEulerXYZ(const glm::vec3& rotation)
    {
        return glm::quat(glm::radians(rotation));
    }

private:
    glm::vec3 m_position;
    glm::mat4 m_rotation;
    glm::mat4 m_scale;
};

}
