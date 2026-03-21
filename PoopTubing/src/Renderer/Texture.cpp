#include "Renderer/Texture.hpp"
#include "Log/Log.hpp"
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace PT
{

Texture::Texture()
{
}

Texture::~Texture()
{
}

void Texture::Load(Path& path)
{
    int nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path.string().c_str(), &m_width, &m_height, &nrChannels, 0);

    Generate();
    UploadData(data);

    stbi_image_free(data);

    CORE_LOG_SUCCESS("Texture initialized");
}

void Texture::Load(int32_t width, int32_t height)
{
    m_width = width;
    m_height = height;

    Generate();
}

void Texture::Unload()
{
    glDeleteTextures(1, &m_id);
}

void Texture::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::UploadData(void* data)
{
    if (data)
    {
        glTextureSubImage2D(m_id, 0, 0, 0, m_width, m_height, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }
    else
    {
        CORE_LOG_ERROR("Failed to load texture");
    }
}

void Texture::Generate()
{
    glCreateTextures(GL_TEXTURE_2D, 1, &m_id);
    glTextureStorage2D(m_id, 1, GL_RGBA8, m_width, m_height);

     // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

}
