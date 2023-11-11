#include "mepch.h"
#include "ImGUILayer.h"
#include "Mimou/Application.h"

#include "imgui.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

namespace Mimou
{
	void ImGUILayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& IO = ImGui::GetIO(); (void)IO;
		IO.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		IO.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		IO.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

		ImGui::StyleColorsDark();
		//ImGui::StyleColorsLight();

		ImGuiStyle& Style = ImGui::GetStyle();
		if (IO.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			Style.WindowRounding = 0.0f;
			Style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		Application* App = Application::GetInstance();
		GLFWwindow* Window = static_cast<GLFWwindow*>(App->GetWindow().GetNativeWindow());

		ImGui_ImplGlfw_InitForOpenGL(Window, true);
		ImGui_ImplOpenGL3_Init();
	}

	void ImGUILayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGUILayer::OnEvent(EventBase& Event)
	{
		if (!m_EventBlocked)
		{
			ImGuiIO& IO = ImGui::GetIO();
			Event.bHandled |= Event.IsInCategory(EventCategoryMouse) & IO.WantCaptureMouse;
			Event.bHandled |= Event.IsInCategory(EventCategoryKeyboard) & IO.WantCaptureKeyboard;
		}
	}

	void ImGUILayer::OnImGUIRender()
	{
	}

	void ImGUILayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void ImGUILayer::End()
	{
		ImGuiIO& IO = ImGui::GetIO();
		Application* App = Application::GetInstance();
		IO.DisplaySize = ImVec2((float)App->GetWindow().GetWidth(), (float)App->GetWindow().GetHeight());

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (IO.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* BackupContext = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(BackupContext);
		}
	}
}
