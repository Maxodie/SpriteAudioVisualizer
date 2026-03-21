#include <PoopTubing.hpp>

class EditorLayer : public PT::Layer
{
public:
    virtual void Update() override
    {
        m_MovementAlpha += 0.00001f;
        glm::vec3 lerpMove = glm::mix(glm::vec3(), glm::vec3(0.0f, 1.0f, 0.0f), m_MovementAlpha);
        m_headLocalTranform.AddOffsetLocation(std::move(lerpMove));

        PT::Renderer::Begin(m_modelTranform);

        PT::Renderer::DrawQuad(m_bodyTexture, m_localTranform);
        PT::Renderer::DrawQuad(m_headTexture, m_headLocalTranform);
        PT::Renderer::DrawQuad(m_leftTexture, m_localTranform);
        PT::Renderer::DrawQuad(m_rightTexture, m_localTranform);

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
        PT::Path mrfrogBodyPath = "TestAssets/mrfrogBody.png";
        m_bodyTexture.Load(mrfrogBodyPath);

        PT::Path mrFrogHeadPath = "TestAssets/mrfrogHead.png";
        m_headTexture.Load(mrFrogHeadPath);

        PT::Path mrFrogLeftEyePath = "TestAssets/mrfrogLeftPupil.png";
        m_leftTexture.Load(mrFrogLeftEyePath);

        PT::Path mrFrogRightEyePath = "TestAssets/mrfrogRightPupil.png";
        m_rightTexture.Load(mrFrogRightEyePath);
    }

    virtual void OnDetach() override
    {
        m_rightTexture.Unload();

        m_leftTexture.Unload();

        m_bodyTexture.Unload();

        m_bodyTexture.Unload();
    }

private:
    PT::Texture m_bodyTexture;
    PT::Texture m_headTexture;
    PT::Texture m_leftTexture;
    PT::Texture m_rightTexture;

    PT::Transform m_localTranform;
    PT::Transform m_headLocalTranform;
    PT::Transform m_modelTranform;

    float m_MovementAlpha = 0.0f;
};

void StartApplication(PT::Application& app)
{
    std::shared_ptr<EditorLayer> layer = app.AddLayer<EditorLayer>();
}
