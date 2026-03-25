#include "Renderer/Renderer.hpp"
#include "Renderer/Transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Renderer/RendererAPI.hpp"
#include "Renderer/Texture.hpp"
#include "Application/Application.hpp"

namespace PT
{
Renderer::Data Renderer::s_data;
uint32_t Renderer::s_shaderProgram;
uint32_t Renderer::s_VBO, Renderer::s_VAO, Renderer::s_EBO;
uint32_t Renderer::s_vertexShader;
uint32_t Renderer::s_fragmentShader;
Camera Renderer::s_camera;

constexpr const  char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec2 aTexCoord;\n"
    "layout (location = 2) in float aTexID;\n"
    "out vec2 TexCoord;\n"
    "out float TexID;\n"
    "uniform mat4 uModel;\n"
    "uniform mat4 uLocal;\n"
    "uniform mat4 uView;\n"
    "uniform mat4 uProjection;\n"
    "void main()\n"
    "{\n"
    "   TexCoord = aTexCoord;\n"
    "   TexID = aTexID;\n"
    "   gl_Position = uProjection * uView * uModel * uLocal * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
constexpr const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec2 TexCoord;\n"
    "in float TexID;\n"
    "uniform sampler2D uTexture;\n"
    "void main()\n"
    "{\n"
    "   FragColor = texture(uTexture, TexCoord);\n"
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

    glGenVertexArrays(1, &s_VAO);
    glGenBuffers(1, &s_VBO);
    glGenBuffers(1, &s_EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(s_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, s_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(s_data.QuadVertices), s_data.QuadVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(s_data.QuadIndices), s_data.QuadIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //rebind it statically bc it will never change
    glBindBuffer(GL_ARRAY_BUFFER, s_VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_EBO);

    // glBindVertexArray(s_VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

    CORE_LOG_SUCCESS("Renderer initialized");

    //setup shader data
    glUseProgram(s_shaderProgram);
    glUniform1i(glGetUniformLocation(s_shaderProgram, "uTexture"), 0);

    //setup camera
    s_camera.Setup(60.f, Application::GetApp().GetWindow().GetAspectRatio(), 0.1f, 11.f);
    glUniformMatrix4fv(glGetUniformLocation(s_shaderProgram, "uView"), 1, GL_FALSE, glm::value_ptr(s_camera.GetView()));
    glUniformMatrix4fv(glGetUniformLocation(s_shaderProgram, "uProjection"), 1, GL_FALSE, glm::value_ptr(s_camera.GetProjection()));
}

void Renderer::Shutdown()
{
    glDeleteVertexArrays(1, &s_VAO);
    glDeleteBuffers(1, &s_VBO);
    glDeleteBuffers(1, &s_EBO);
    glDeleteProgram(s_shaderProgram);
    CORE_LOG_SUCCESS("Renderer shutdown");
}

void Renderer::Begin(const Transform& model)
{
    RendererAPI::Clear();
    glUniformMatrix4fv(glGetUniformLocation(s_shaderProgram, "uModel"), 1, GL_FALSE, glm::value_ptr(model.GetModel()));
}

void Renderer::End()
{
}

void Renderer::DrawQuad(const Texture& tex, const Transform& local)
{
    tex.Bind();
    glUniformMatrix4fv(glGetUniformLocation(s_shaderProgram, "uLocal"), 1, GL_FALSE, glm::value_ptr(local.GetModel()));
    Flush();
}

void Renderer::Flush()
{
    // bind the vertex and index data
    // glBindBuffer(GL_ARRAY_BUFFER, s_VBO);
    // glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(s_data.QuadVertices), s_data.QuadVertices);
    //
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_EBO);
    // glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(s_data.QuadIndices), s_data.QuadIndices);

    //draw and reset buffer
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    //unbind buffers for security reason
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

}
