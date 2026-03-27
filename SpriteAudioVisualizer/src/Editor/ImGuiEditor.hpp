#pragma once

namespace PT
{

class ImGuiEditor
{
public:
    static void Init();
    static void Shutdown();

    static void Begin();
    static void End();
};

}
