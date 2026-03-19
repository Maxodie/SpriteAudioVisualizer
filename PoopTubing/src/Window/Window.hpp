#pragma once
#include "Core.hpp"
#include "Renderer/OpenglGraphicsContext.hpp"

struct GLFWwindow;
namespace PT
{

class Window
{
public:
    using Callback = std::function<void(class Event&)>;

    struct Data
    {
        uint32_t Width, Height;
        std::string Name;
        Callback callback;
    };

    Window();
    ~Window();

    void Create(Data&& data);
    void Destroy();
    void PollEvent();
    void SwapBuffers();

    PT_INLINE void* GetNative()
    {
        return m_native;
    }

    PT_INLINE void SetDataSize(uint32_t width, uint32_t height)
    {
        m_data.Width = width;
        m_data.Height = height;
    }

    PT_INLINE const Data& GetData()
    {
        return m_data;
    }

private:
    GLFWwindow* m_native;
    Data m_data;
    OpenglGraphicsContext m_openglGraphicsContext;
};

}
