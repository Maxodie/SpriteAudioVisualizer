#pragma once
#include "Application/LayerStack.hpp"
#include "Window/Window.hpp"
#include "Core.hpp"

namespace PT
{

class Event;

class Application
{
public:
    Application();
    ~Application();

    void Init();
    void Shutdown();

    void Run();
    void Stop();

    template<typename TLayer, typename ... TArgs>
    PT_INLINE std::shared_ptr<TLayer> AddLayer(TArgs&&... args)
    {
        return m_layerStack.AddLayer<TLayer>(std::forward<TArgs>(args)...);
    }

    template<typename TLayer, typename ... TArgs>
    PT_INLINE void RemoveLayer()
    {
        // return m_layerStack.RemoveLayer<TLayer>();
        // send action as event
    }

    PT_INLINE const Window& GetWindow() const
    {
        return m_window;
    }

    PT_INLINE static const Application& GetApp()
    {
        if(!s_instance)
        {
            s_instance = &Create();
        }

        return *s_instance;
    }

    PT_INLINE static Application& Create()
    {
        PT_CORE_ASSERT(!s_instance, "application should not be created multiple times at once");

        s_instance = new Application();
        CORE_LOG_SUCCESS("App created");
        return *s_instance;
    }

    PT_INLINE static void Destroy()
    {
        delete s_instance;
        s_instance = nullptr;
        CORE_LOG_SUCCESS("App destroyed");
    }

private:
    void OnEvent(Event& event);
    bool OnWindowClosedCallback(const class WindowClosedEvent& event);
    bool OnWindowResizedCallback(const class WindowResizeEvent& event);

private:
    static Application* s_instance;
    LayerStack m_layerStack;
    Window m_window;

    bool m_isRunning = false;
    char padding[6];
};

}
