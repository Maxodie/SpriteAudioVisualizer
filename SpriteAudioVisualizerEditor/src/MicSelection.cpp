#include "Application/Application.hpp"
#include <MicSelection.hpp>
#include <imgui.h>

void MicSelection::Update(float deltaTime)
{

}

void MicSelection::OnEvent(class PT::Event& event)
{

}

void MicSelection::UpdateGUI()
{
    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoScrollbar;
    window_flags |= ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoCollapse;
    window_flags |= ImGuiWindowFlags_NoNav;
    // window_flags |= ImGuiWindowFlags_UnsavedDocument;

    // ImGui::Begin("Microphone selection", m_isOpen, window_flags);
    if(ImGui::Begin("Microphone selection", &m_isOpen, window_flags))
    {
        PT::Microphone& mic = PT::Microphone::Get();

#ifdef PT_EDITOR
        ImGui::Text("with Editor version");
#endif

        if(ImGui::BeginChild("Entity Hierarchy"))
        {
            for(size_t i = 0; i < mic.GetDeviceNum(); ++i)
            {
                std::string_view deviceName = mic.GetDevice(i);

                if(ImGui::Button(deviceName.data()))
                {
                    m_onMicrphoneSelectedCb(i);
                    PT::Application::GetApp().RemoveLayer<MicSelection>();
                }
            }
            ImGui::EndChild();
        }

        ImGui::End();
    }
}

void MicSelection::OnAttach()
{
}

void MicSelection::OnDetach()
{

}
