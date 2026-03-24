#include "Renderer/Camera.hpp"
#include "glm/ext.hpp"

namespace PT
{

void Camera::Setup(float fov, float aspectRatio, float near, float far)
{
    m_projection = glm::perspective(glm::radians(fov), aspectRatio, near, far);
    m_view = glm::lookAt(
                glm::vec3(0.0f, 0.0f, 1.0f),
  		        glm::vec3(0.0f, 0.0f, 0.0f),
  		        glm::vec3(0.0f, 1.0f, 0.0f)
             );

    CORE_LOG_SUCCESS("Camera setup");
}

}
