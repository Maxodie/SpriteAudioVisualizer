#pragma once

namespace PT
{

class OpenglGraphicsContext
{
public:
    OpenglGraphicsContext();
    ~OpenglGraphicsContext();

    void PrepareCreation();
    void Init();
    void Shutdown();
};

}
