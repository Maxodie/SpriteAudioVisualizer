#include "Renderer/Transform.hpp"
#include "glm/trigonometric.hpp"
#include <PoopTubing.hpp>
#include <glm/gtx/quaternion.hpp>

class EditorLayer : public PT::Layer
{
public:
    virtual void Update(float deltaTime) override
    {
        long clipPos = PT::Microphone::Get().GetStreamReadPosition(m_micDevice);
        float loudness = 0.0f;
        if(!GetLoudnessFromWaves(clipPos, loudness))
        {
            return;
        }

        glm::vec3 headLocation = glm::vec3(0.0f, 0.5f, 0.0f) * loudness;
        glm::vec3 headLerpMove = glm::mix(m_headLocalTranform.GetLocation(), headLocation, deltaTime * 100.f);
        m_headLocalTranform.SetLocation(std::move(headLerpMove));

        glm::vec3 bodyLocation = glm::vec3(0.0f, -0.2f, 0.0f) * loudness;
        glm::vec3 bodyLerpMove = glm::mix(m_bodylocalTranform.GetLocation(), bodyLocation, deltaTime * 100.f);
        m_bodylocalTranform.SetLocation(std::move(bodyLerpMove));

        glm::quat modelMaxRotationOffsetDeg = PT::Transform::MakeQuatFromEulerXYZ(glm::vec3(-15.0f, 45.0f, 5.f) * loudness);
        glm::quat modelRotLerpMove = glm::slerp(m_modelTranform.GetRotation(), modelMaxRotationOffsetDeg, deltaTime * 100.f);
        m_modelTranform.SetRotation(std::move(modelRotLerpMove));

        // m_rotAlpha += 0.00001f;
        // glm::vec3 lerpRot = glm::vec3(0.0f, 1.0f, 0.0f);
        // m_modelTranform.AddOffsetRotation(std::move(lerpRot), loudness);

        PT::Renderer::Begin(m_modelTranform);

        PT::Renderer::DrawQuad(m_bodyTexture, m_bodylocalTranform);
        PT::Renderer::DrawQuad(m_headTexture, m_headLocalTranform);
        PT::Renderer::DrawQuad(m_leftTexture, m_headLocalTranform);
        PT::Renderer::DrawQuad(m_rightTexture, m_headLocalTranform);

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

        PT::Microphone& mic = PT::Microphone::Get();
        m_micDevice = mic.GetDeviceNum() - 1;
        std::string deviceName = mic.GetDevice(m_micDevice);
        CLIENT_LOG_DEBUG("Microphone device selected : %s", deviceName.c_str());

        mic.StartStream(m_micDevice, s_micFramePerBuffer);

        m_modelTranform.AddOffsetLocation(glm::vec3(0.f, -3.5f, 0.f));
    }

    virtual void OnDetach() override
    {
        PT::Microphone::Get().StopStream(m_micDevice);

        m_rightTexture.Unload();

        m_leftTexture.Unload();

        m_headTexture.Unload();

        m_bodyTexture.Unload();
    }

    bool GetLoudnessFromWaves(long clipPos, float& outValue)
    {
        long startPos = clipPos - s_micFramePerBuffer;
        if(startPos <= 0)
        {
            return false;
        }

        const float* inputData = PT::Microphone::Get().GetStreamInputData(m_micDevice);

        float vol = 0;

        for(unsigned long i = 0; i < s_micFramePerBuffer; ++i)
        {
            vol += std::abs(inputData[i]);
        }

        if(vol > s_micDetectionThreshold)
        {
            outValue = std::clamp(vol / 10.f, s_minValue, 1.0f);
            return true;
        }

        outValue = 0.0f;
        return true;
    }

private:
    PT::Texture m_bodyTexture;
    PT::Texture m_headTexture;
    PT::Texture m_leftTexture;
    PT::Texture m_rightTexture;

    PT::Transform m_modelTranform{glm::vec3(3.2f, 3.2f, 3.2f)};
    PT::Transform m_bodylocalTranform;
    PT::Transform m_headLocalTranform;

    float m_movementAlpha = 0.0f;
    float m_rotAlpha = 0.0f;

    int32_t m_micDevice;
    static constexpr unsigned long s_micFramePerBuffer = 256;
    static constexpr unsigned long s_micSampleSize = 64;
    static constexpr float s_micDetectionThreshold = 1.5f;
    static constexpr float s_minValue = 0.5f;
};

void StartApplication(PT::Application& app)
{
    std::shared_ptr<EditorLayer> layer = app.AddLayer<EditorLayer>();
}
