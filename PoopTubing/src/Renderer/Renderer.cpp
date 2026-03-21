#include "Renderer/Renderer.hpp"
#include "Log/Log.hpp"
#include "Renderer/RendererAPI.hpp"
#include "Renderer/Texture.hpp"

namespace PT
{
Renderer::Data Renderer::s_data;
uint32_t Renderer::s_shaderProgram;
uint32_t Renderer::s_VBO, Renderer::s_VAO, Renderer::s_EBO;
uint32_t Renderer::s_vertexShader;
uint32_t Renderer::s_fragmentShader;

constexpr const  char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec2 aTexCoord;\n"
    "layout (location = 2) in float aTexID;\n"
    "out vec2 TexCoord;\n"
    "out float TexID;\n"
    "void main()\n"
    "{\n"
    "   TexCoord = aTexCoord;\n"
    "   TexID = aTexID;\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
constexpr const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec2 TexCoord;\n"
    "in float TexID;\n"
    "uniform sampler2D uTextures[32];\n"
    "void main()\n"
    "{\n"
    // "   FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
    "   FragColor = texture(uTextures[int(round(TexID))], TexCoord);\n"
    "}\n\0";


void Renderer::Init()
{
    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    int success;
    s_vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(s_vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(s_vertexShader);
    // check for shader compile errors
    char infoLog[512];
    glGetShaderiv(s_vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(s_vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    s_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(s_fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(s_fragmentShader);
    // check for shader compile errors
    glGetShaderiv(s_fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(s_fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    s_shaderProgram = glCreateProgram();
    glAttachShader(s_shaderProgram, s_vertexShader);
    glAttachShader(s_shaderProgram, s_fragmentShader);
    glLinkProgram(s_shaderProgram);
    // check for linking errors
    glGetProgramiv(s_shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(s_shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(s_vertexShader);
    glDeleteShader(s_fragmentShader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    //setup buffers
    s_data.StartVertex = static_cast<Vertex*>(std::malloc(s_data.VertexBufferSize * sizeof(Vertex)));
    s_data.TopVertex = s_data.StartVertex;
    s_data.StartIndex = static_cast<uint32_t*>(std::malloc(s_data.IndexBufferSize * sizeof(uint32_t)));

    //setup static index buffer
    size_t offset = 0;
    for(size_t i = 0; i < s_data.IndexBufferSize; i += s_data.QuadIndexAmount)
    {
        for(size_t j = 0; j < s_data.QuadIndexAmount; ++j)
        {
            s_data.StartIndex[i + j] = offset + s_data.QuadIndices[j];
        }
        offset += 4;
    }

    glGenVertexArrays(1, &s_VAO);
    glGenBuffers(1, &s_VBO);
    glGenBuffers(1, &s_EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(s_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, s_VBO);
    glBufferData(GL_ARRAY_BUFFER, s_data.VertexBufferSize * sizeof(Vertex), s_data.StartVertex, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, s_data.IndexBufferSize * sizeof(uint32_t), s_data.StartIndex, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // glBindVertexArray(s_VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

    CORE_LOG_SUCCESS("Renderer initialized");

    //setup shader data
    int sampler[s_data.MaxTextureAmount];
    for(uint32_t i = 0; i < s_data.MaxTextureAmount; ++i)
    {
        sampler[i] = i;
    }

    uint32_t whiteData = 0xffffffff;
    Texture whiteTexture;
    whiteTexture.Load(1, 1);
    whiteTexture.UploadData(&whiteData);

    AddTexture(whiteTexture);

    whiteTexture.Unload();

    glUseProgram(s_shaderProgram);
    glUniform1iv(glGetUniformLocation(s_shaderProgram, "uTextures"), s_data.MaxTextureAmount, sampler);

}

void Renderer::Shutdown()
{
    CORE_LOG_SUCCESS("Test texture shutdown");

    glDeleteVertexArrays(1, &s_VAO);
    glDeleteBuffers(1, &s_VBO);
    glDeleteBuffers(1, &s_EBO);
    glDeleteProgram(s_shaderProgram);
    CORE_LOG_SUCCESS("Renderer shutdown");
}

void Renderer::Begin()
{
    RendererAPI::Clear();
}

void Renderer::End()
{
    Flush();
}

void Renderer::DrawQuad(const Texture& tex)
{
    //TODO HANDLE BUFFER OVEERFLOW (s_data.VertexBuffersize < s_data.CurrentVertexBufferSize) same for index

    uint32_t texID = AddTexture(tex);

    s_data.TopVertex->Position = s_data.QuadVertices[0];
    s_data.TopVertex->Position += 0.01f * s_data.IndexCount;
    s_data.TopVertex->TexCoord = s_data.QuadTexCoord[0];
    s_data.TopVertex->TexID = texID;
    ++s_data.TopVertex;

    s_data.TopVertex->Position = s_data.QuadVertices[1];
    s_data.TopVertex->Position += 0.01f * s_data.IndexCount;
    s_data.TopVertex->TexCoord = s_data.QuadTexCoord[1];
    s_data.TopVertex->TexID = texID;
    ++s_data.TopVertex;

    s_data.TopVertex->Position = s_data.QuadVertices[2];
    s_data.TopVertex->Position += 0.01f * s_data.IndexCount;
    s_data.TopVertex->TexCoord = s_data.QuadTexCoord[2];
    s_data.TopVertex->TexID = texID;
    ++s_data.TopVertex;

    s_data.TopVertex->Position = s_data.QuadVertices[3];
    s_data.TopVertex->Position += 0.01f * s_data.IndexCount;
    s_data.TopVertex->TexCoord = s_data.QuadTexCoord[3];
    s_data.TopVertex->TexID = texID;
    ++s_data.TopVertex;

    s_data.IndexCount += s_data.QuadIndexAmount;
}

void Renderer::Flush()
{
    //bind the vertex and index data
    glBindBuffer(GL_ARRAY_BUFFER, s_VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, s_data.VertexBufferSize * sizeof(Vertex), s_data.StartVertex);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_EBO);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, s_data.IndexBufferSize * sizeof(uint32_t), s_data.StartIndex);

    //bind textures
    for(uint32_t i = 0; i < s_data.TextureCount; ++i)
    {
        glBindTexture(GL_TEXTURE_2D, s_data.Textures[i]->GetID());
    }

    //draw and reset buffer
    glDrawElements(GL_TRIANGLES, s_data.IndexCount, GL_UNSIGNED_INT, 0);
    s_data.TopVertex = s_data.StartVertex;
    s_data.IndexCount = 0;
    s_data.TextureCount = 1;

    //unbind buffers for security reason
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

uint32_t Renderer::AddTexture(const Texture& tex)
{
    for(size_t i = 0; i < s_data.TextureCount; ++i)
    {
        if(tex.GetID() == s_data.Textures[i]->GetID())
        {
            return tex.GetID();
        }
    }

    s_data.Textures[s_data.TextureCount] = &tex;
    return s_data.TextureCount++;
}

}
