#include "Window/GraphicsContext.hpp"
#include "Log/Log.hpp"
#include <GLFW/glfw3.h>

namespace PT
{

void GraphicsContext::Init()
{
    if(!glfwInit())
    {
        CORE_LOG_ERROR("Failed to initialize glfw");
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    CORE_LOG_SUCCESS("glfw graphics context initialized");
}

void GraphicsContext::Shutdown()
{
    glfwTerminate();
    CORE_LOG_SUCCESS("Graphics context has been shutdown");
}

}
