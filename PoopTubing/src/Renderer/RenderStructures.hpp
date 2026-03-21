#pragma once
#include <glm/glm.hpp>

namespace PT
{

struct Vertex
{
    glm::vec3 Position;
    glm::vec2 TexCoord;
    uint32_t TexID;
};

}

