#include "Audio/Microphone.hpp"
#include "Log/Log.hpp"
#include <PoopTubing.hpp>

class EditorLayer : public PT::Layer
{
public:
    virtual void Update() override
    {
        long clipPos = PT::Microphone::Get().GetStreamReadPosition(m_micDevice);
        float loudness = GetLoudnessFromWaves(clipPos);

        // m_movementAlpha += 0.00001f;
        glm::vec3 headLocation = glm::vec3(0.0f, 0.5f, 0.0f) * loudness;
        glm::vec3 lerpMove = glm::mix(m_headLocalTranform.GetLocation(), headLocation, 0.05f);
        m_headLocalTranform.SetLocation(std::move(lerpMove));

        // m_rotAlpha += 0.00001f;
        // glm::vec3 lerpRot = glm::vec3(0.0f, 1.0f, 0.0f);
        // m_modelTranform.AddOffsetRotation(std::move(lerpRot), loudness);

        PT::Renderer::Begin(m_modelTranform);

        PT::Renderer::DrawQuad(m_bodyTexture, m_localTranform);
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
    }

    virtual void OnDetach() override
    {
        PT::Microphone::Get().StopStream(m_micDevice);

        m_rightTexture.Unload();

        m_leftTexture.Unload();

        m_headTexture.Unload();

        m_bodyTexture.Unload();
    }

    float GetLoudnessFromWaves(long clipPos)
    {
        long startPos = clipPos - s_micFramePerBuffer;
        if(startPos <= 0)
        {
            return 0.0f;
        }

        const float* inputData = PT::Microphone::Get().GetStreamInputData(m_micDevice);
        int dispSize = 100;

        float vol = 0;

        for(unsigned long i = 0; i < s_micSampleSize; ++i)
        {
            vol += std::abs(inputData[i]);
        }

        if(vol > s_micDetectionThreshold)
        {
            return std::max(vol / static_cast<float>(s_micSampleSize), s_minValue);
        }

        return 0.0f;
    }

private:
    PT::Texture m_bodyTexture;
    PT::Texture m_headTexture;
    PT::Texture m_leftTexture;
    PT::Texture m_rightTexture;

    PT::Transform m_localTranform;
    PT::Transform m_headLocalTranform;
    PT::Transform m_modelTranform;

    float m_movementAlpha = 0.0f;
    float m_rotAlpha = 0.0f;

    int32_t m_micDevice;
    static constexpr unsigned long s_micFramePerBuffer = 256;
    static constexpr unsigned long s_micSampleSize = 64;
    static constexpr float s_micDetectionThreshold = 0.8f;
    static constexpr float s_minValue = 0.5f;
};

void StartApplication(PT::Application& app)
{
    std::shared_ptr<EditorLayer> layer = app.AddLayer<EditorLayer>();
}
