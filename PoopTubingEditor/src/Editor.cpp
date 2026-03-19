#include <PoopTubing.hpp>

class EditorLayer : public PT::Layer
{
public:
    virtual void Update() override
    {
        PT::Renderer::Begin();
        PT::Renderer::End();
    }

    virtual void OnEvent(PT::Event& event) override
    {

    }

    virtual void UpdateGUI() override
    {

    }

    virtual void OnAttach() override
    {

    }

    virtual void OnDetach() override
    {

    }
};

void StartApplication(PT::Application& app)
{
    std::shared_ptr<EditorLayer> layer = app.AddLayer<EditorLayer>();
}
