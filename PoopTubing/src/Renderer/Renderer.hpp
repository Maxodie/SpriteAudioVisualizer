#pragma once
#include "Core.hpp"
#include "Renderer/RenderStructures.hpp"

namespace PT
{

class Renderer
{
private:
    struct Data
    {
        static constexpr uint32_t QuadIndexAmount = 6;
        static constexpr uint32_t QuadVertexAmount = 4;

        static constexpr glm::vec3 QuadVertices[] = {
            {0.5f,  0.5f, 0.0f},  // top right
            {0.5f, -0.5f, 0.0f},  // bottom right
            {-0.5f, -0.5f, 0.0f},  // bottom left
            {-0.5f,  0.5f, 0.0f},   // top left
        };

        static constexpr glm::vec2 QuadTexCoord[] = {
            {1.0f, 1.0f},  // top right
            {1.0f, 0.0f},  // bottom right
            {0.0f, 0.0f},  // bottom left
            {0.0f, 1.0f}    // top left
        };

        static constexpr uint32_t QuadIndices[] = {  // note that we start from 0!
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
        };

        static constexpr size_t VertexBufferSize = QuadVertexAmount * 10;
        Vertex* StartVertex;
        Vertex* TopVertex;

        static constexpr size_t IndexBufferSize = QuadIndexAmount * 10;
        uint32_t* StartIndex;
        size_t IndexCount;

        static constexpr uint32_t MaxTextureAmount = 32;
        std::array<class Texture const*, 32> Textures;
        size_t TextureCount;
    };

public:
    static void Init();
    static void Shutdown();
    static void Begin();
    static void End();

    static void DrawQuad(const Texture& texture);
    static void Flush();
    static uint32_t AddTexture(const Texture& tex);

private:
    static Data s_data;
    static uint32_t s_shaderProgram;
    static uint32_t s_VBO, s_VAO, s_EBO;
    static uint32_t s_vertexShader;
    static uint32_t s_fragmentShader;
};

}
