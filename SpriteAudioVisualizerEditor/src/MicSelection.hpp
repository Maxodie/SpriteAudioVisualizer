#pragma once
#include <Editor.hpp>

class MicSelection : public PT::Layer
{
public:
    MicSelection() = default;
    virtual ~MicSelection() = default;

    virtual void Update(float deltaTime) override;
    virtual void OnEvent(class PT::Event& event) override;
    virtual void UpdateGUI() override;
    virtual void OnAttach() override;
    virtual void OnDetach() override;

    PT_FORCE_INLINE void BindOnMicSelected(const std::function<void(size_t)>& callback)
    {
        m_onMicrphoneSelectedCb = callback;
    }

private:
    bool m_isOpen = true;
    std::function<void(size_t)> m_onMicrphoneSelectedCb;
};
