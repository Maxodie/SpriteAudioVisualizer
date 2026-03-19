#pragma once
#include "Application/LayerStack.hpp"
#include "Window/Window.hpp"

namespace PT
{

class Event;

class Application
{
public:
    Application();
    ~Application();
    void Run();
    void Stop();

    template<typename TLayer, typename ... TArgs>
    std::shared_ptr<TLayer> AddLayer(TArgs&&... args)
    {
        return m_layerStack.AddLayer<TLayer>(std::forward<TArgs>(args)...);
    }

private:
    void OnEvent(Event& event);
    bool OnWindowClosedCallback(const class WindowClosedEvent& event);
    bool OnWindowResizedCallback(const class WindowResizeEvent& event);

private:
    LayerStack m_layerStack;
    Window m_window;

    bool m_isRunning = false;
    char padding[6];
};

}
