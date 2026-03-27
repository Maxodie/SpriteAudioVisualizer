#include "Application.hpp"
#include "Audio/Microphone.hpp"
#include "Editor/ImGuiEditor.hpp"
#include "Event/Event.hpp"
#include "Event/WindowEvent.hpp"
#include "Window/GraphicsContext.hpp"
#include "Renderer/RendererAPI.hpp"
#include "Renderer/Renderer.hpp"
#include <chrono>

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

    ImGuiEditor::Init();

    Microphone::Init();
    CORE_LOG_SUCCESS("App Initialized");
}

void Application::Shutdown()
{
    m_layerStack.ClearLayers();
    Microphone::Shutdown();

    ImGuiEditor::Shutdown();
    Renderer::Shutdown();
    m_window.Destroy();
    GraphicsContext::Shutdown();
    CORE_LOG_SUCCESS("App Shutdown");
}

void Application::Run()
{
    m_dt = 1.f / 60.f;

    while(m_isRunning)
    {
        m_beginTicks = std::chrono::high_resolution_clock::now();

        m_window.PollEvent();
        PollTasks();

        for(auto& layer : m_layerStack.GetLayers())
        {
            layer->Update(m_dt);
        }

        ImGuiEditor::Begin();
        for(auto& layer : m_layerStack.GetLayers())
        {
            layer->UpdateGUI();
        }
        ImGuiEditor::End();

        m_window.SwapBuffers();


        m_endTicks = std::chrono::high_resolution_clock::now();
        m_dt = std::chrono::duration_cast<std::chrono::milliseconds>(m_endTicks - m_beginTicks).count() / 1000.f;

        if(m_dt > 1.f)
        {
            // m_dt = 1.f / 60.f;
        }
        m_beginTicks = m_endTicks;
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

void Application::PollTasks()
{
    while(!m_taskEventQueue.empty())
    {
        m_taskEventQueue.front()();
        m_taskEventQueue.pop();
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
