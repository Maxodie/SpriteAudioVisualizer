#include "Editor/ImGuiEditor.hpp"
#include "Application/Application.hpp"

#include <imgui.h>
#include "Log/Log.hpp"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

namespace PT
{

void ImGuiEditor::Init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui_ImplGlfw_InitForOpenGL(Application::GetApp().GetWindow().GetNative(), true);
    ImGui_ImplOpenGL3_Init("#version 410 core");

    CORE_LOG_SUCCESS("ImGuiEditor initialized");
}

void ImGuiEditor::Shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    CORE_LOG_SUCCESS("ImGuiEditor shutdown");
}

void ImGuiEditor::Begin()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiEditor::End()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

}
