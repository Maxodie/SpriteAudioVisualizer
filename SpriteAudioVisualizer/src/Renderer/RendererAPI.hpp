#pragma once
#include "Core.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace PT
{

class RendererAPI
{
public:

    PT_INLINE static void SetViewport(size_t width, size_t height)
    {
        glViewport(0, 0, width, height);
    }

    PT_INLINE static void SetClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    PT_INLINE static void Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
};

}
