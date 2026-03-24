#include "Application.hpp"
#include "Audio/Microphone.hpp"
#include "Event/Event.hpp"
#include "Event/WindowEvent.hpp"
#include "Window/GraphicsContext.hpp"
#include "Renderer/RendererAPI.hpp"
#include "Renderer/Renderer.hpp"

namespace PT
{

Application* Application::s_instance = nullptr;

Application::Application()
{
}

Application::~Application()
{
}

void Application::Init()
{
    m_isRunning = true;

    GraphicsContext::Init();

    m_window.Create({1280, 720, "PoopTubing", PT_BIND_FUN1(Application::OnEvent)});

    RendererAPI::SetClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 0.f));
    RendererAPI::SetViewport(m_window.GetData().Width, m_window.GetData().Height);

    Renderer::Init();

    Microphone::Init();
    CORE_LOG_SUCCESS("App Initialized");
}

void Application::Shutdown()
{
    m_layerStack.ClearLayers();
    Microphone::Shutdown();

    Renderer::Shutdown();
    m_window.Destroy();
    GraphicsContext::Shutdown();
    CORE_LOG_SUCCESS("App Shutdown");
}

void Application::Run()
{
    while(m_isRunning)
    {
        m_window.PollEvent();

        for(auto& layer : m_layerStack.GetLayers())
        {
            layer->Update();
        }

        for(auto& layer : m_layerStack.GetLayers())
        {
            layer->UpdateGUI();
        }

        m_window.SwapBuffers();
    }
}

void Application::Stop()
{
    m_isRunning = false;
}

void Application::OnEvent(Event& event)
{
    EventDispatcher dispatcher{event};
    dispatcher.Dispatch<WindowClosedEvent>(PT_BIND_FUN1(Application::OnWindowClosedCallback));
    dispatcher.Dispatch<WindowResizeEvent>(PT_BIND_FUN1(Application::OnWindowResizedCallback));

    for(auto& layer : m_layerStack.GetLayers())
    {
        if(!event.Handled)
        {
            layer->OnEvent(event);
        }
    }
}

bool Application::OnWindowClosedCallback(const WindowClosedEvent& event)
{
    Stop();
    return true;
}

bool Application::OnWindowResizedCallback(const WindowResizeEvent& event)
{
    if(event.WindowData.Width != 0 && event.WindowData.Height != 0)
    {
        CORE_LOG_ERROR("This should not happened, please check the window creation parameters");
    }

    return true;
}

};
