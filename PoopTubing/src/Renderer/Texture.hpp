#pragma once
#include "Core.hpp"
#include "Utils/FileSystem.hpp"

namespace PT
{

class Texture
{
public:
    Texture();
    ~Texture();

    void Load(Path& path);
    void Load(int32_t width, int32_t height);
    void Unload();

    void UploadData(void* data);

    PT_INLINE uint32_t GetID() const
    {
        return m_id;
    }

private:
    void Generate();

private:
    uint32_t m_id;
    int32_t m_width;
    int32_t m_height;
};

}
