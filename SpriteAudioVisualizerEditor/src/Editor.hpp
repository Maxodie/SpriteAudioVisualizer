#pragma once
#include <PoopTubing.hpp>

class EditorLayer : public PT::Layer
{
public:
    virtual void Update(float deltaTime) override;
    virtual void OnEvent(PT::Event& event) override;
    virtual void UpdateGUI() override;
    virtual void OnAttach() override;
    virtual void OnDetach() override;

    bool GetLoudnessFromWaves(long clipPos, float& outValue);

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

    int32_t m_micDevice = -1;
    bool m_isMicSelected = false;
    static constexpr unsigned long s_micFramePerBuffer = 256;
    static constexpr unsigned long s_micSampleSize = 64;
    static constexpr float s_micDetectionThreshold = 1.5f;
    static constexpr float s_minValue = 0.5f;
};
