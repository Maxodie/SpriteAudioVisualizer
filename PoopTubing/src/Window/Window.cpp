#include "Window/Window.hpp"
#include "Event/WindowEvent.hpp"
#include <GLFW/glfw3.h>

namespace PT
{

Window::Window()
    : m_native(nullptr)
{
}

Window::~Window()
{
    m_openglGraphicsContext.Shutdown();
    Destroy();
    CORE_LOG_SUCCESS("glfw window destroyed");
}

void Window::Create(Data&& data)
{
    m_data = std::move(data);

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    m_openglGraphicsContext.PrepareCreation();

    m_native = glfwCreateWindow(m_data.Width, m_data.Height, m_data.Name.c_str(), NULL, NULL);
    if(!m_native)
    {
        PT_CORE_ASSERT(false, "Failed to create glfw window");
    }
    glfwMakeContextCurrent(m_native);

    m_openglGraphicsContext.Init();

    glfwSetWindowUserPointer(m_native, &m_data);

    glfwSetWindowCloseCallback(
        m_native,
        [](GLFWwindow* window)
        {
            Data* data = static_cast<Data*>(glfwGetWindowUserPointer(window));
            PT_CORE_ASSERT(data, "fail to retreive the glfw window user data");

            WindowClosedEvent windowClosedEvent{*data};
            data->callback(windowClosedEvent);
        }
    );

    glfwSetWindowSizeCallback(
        m_native,
        [](GLFWwindow* window, int width, int height)
        {
            Data* data = static_cast<Data*>(glfwGetWindowUserPointer(window));
            PT_CORE_ASSERT(data, "fail to retreive the glfw window user data");

            data->Width = width;
            data->Height = height;
            WindowResizeEvent windowClosedEvent{*data};
            data->callback(windowClosedEvent);
        }
    );

    CORE_LOG_SUCCESS("glfw window created");
}

void Window::Destroy()
{
    if(m_native)
    {
        glfwDestroyWindow(m_native);
        m_native = nullptr;
    }
    CORE_LOG_SUCCESS("glfw window destroyed");
}

void Window::PollEvent()
{
    glfwPollEvents();
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(m_native);
}

}
