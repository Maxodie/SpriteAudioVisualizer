#include "EntryPoint.hpp"

int main()
{
    PT::Application& app = PT::Application::Create();
    app.Init();

    StartApplication(app);
    app.Run();

    app.Shutdown();
    PT::Application::Destroy();
}
