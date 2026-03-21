#pragma once
#include "Core.hpp"
#include "Renderer/RenderStructures.hpp"
#include "Renderer/Camera.hpp"

namespace PT
{

class Renderer
{
private:
    struct Data
    {
        static constexpr uint32_t QuadIndexAmount = 6;
        static constexpr uint32_t QuadVertexAmount = 4;

        static constexpr float QuadVertices[] = {
            0.5f,  0.5f, 0.0f, 1.0f, 1.0f,// top right
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,// bottom right
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f   // top left
        };

        // static constexpr glm::vec2 QuadTexCoord[] = {
        //     {1.0f, 1.0f},  // top right
        //     {1.0f, 0.0f},  // bottom right
        //     {0.0f, 0.0f},  // bottom left
        //     {0.0f, 1.0f}    // top left
        // };

        static constexpr uint32_t QuadIndices[] = {  // note that we start from 0!
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
        };
    };

public:
    static void Init();
    static void Shutdown();
    static void Begin(const class Transform& model);
    static void End();

    static void DrawQuad(const class Texture& texture, const Transform& local);
    static void Flush();

private:
    static Data s_data;
    static uint32_t s_shaderProgram;
    static uint32_t s_VBO, s_VAO, s_EBO;
    static uint32_t s_vertexShader;
    static uint32_t s_fragmentShader;

    static Camera s_camera;
};

}
