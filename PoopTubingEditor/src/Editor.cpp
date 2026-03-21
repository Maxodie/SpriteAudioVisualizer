#include <PoopTubing.hpp>

class EditorLayer : public PT::Layer
{
public:
    virtual void Update() override
    {
        PT::Renderer::Begin();
        PT::Renderer::DrawQuad(texture);
        PT::Renderer::DrawQuad(texture);
        PT::Renderer::DrawQuad(texture);
        PT::Renderer::DrawQuad(texture);
        PT::Renderer::DrawQuad(texture);
        PT::Renderer::DrawQuad(texture);
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
        PT::Path mrFrogPath = "TestAssets/mrFrog.png";
        texture.Load(mrFrogPath);
    }

    virtual void OnDetach() override
    {
        texture.Unload();
    }

private:
    PT::Texture texture;
};

void StartApplication(PT::Application& app)
{
    std::shared_ptr<EditorLayer> layer = app.AddLayer<EditorLayer>();
}
