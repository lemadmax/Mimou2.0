#include "EditorLayer.h"

EditorLayer::EditorLayer()
{
	RenderCommand::ClearDepth();


	EditorGridShader = Shader::Create("Assets/Shaders/EditorGrid.glsl"); 
	EditorGridVA = VertexArray::Create();
	uint32_t Indices[6] =
	{
		0, 1, 2, 1, 0, 3
	};
	Ref<IndexBuffer> IndexBuffer;
	IndexBuffer = IndexBuffer::Create(Indices, 6);
	EditorGridVA->AddIndexBuffer(IndexBuffer);

	ShaderLibrary::GetInstance()->Load("Texture Shader", "Assets/Shaders/Texture.glsl");
	ShaderLibrary::GetInstance()->Load("Lambert Shader", "Assets/Shaders/LambertShader.glsl");
}

EditorLayer::~EditorLayer()
{
}

void EditorLayer::OnAttach()
{
	uint32_t Width = Application::GetInstance()->GetWindow().GetWidth();
	uint32_t Height = Application::GetInstance()->GetWindow().GetHeight();
	m_FrameBuffer = FrameBuffer::Create({ Width , Height });

	m_ActiveScene = CreateRef<Scene>("Editor Test Scene");

	m_TestTexture = Texture2D::Create("Assets/Textures/duxin.jpg");

	ShowPanel(PanelType::SceneHierarchyPanel, m_ActiveScene->GetName());

	Ref<GameObject> TestGB0 = m_ActiveScene->CreateGameObject();
	TestGB0->AddComponent<StaticMeshComponent>(StaticMeshLibrary::CreateSquareVA(2, 0), CreateRef<Material>(glm::vec3(0.2, 0.3, 0.4), glm::vec3(0.2, 0.3, 0.4), glm::vec4(0.7, 0.6, 0.6, 1.0), 1.0f, ShaderLibrary::GetInstance()->Get("Texture Shader")));
	StaticMeshComponent& MeshComp = TestGB0->GetComponent<StaticMeshComponent>();
	MeshComp.Mat->SetTexture(m_TestTexture);
	//TransformComponent& TransformComp = TestGB0->GetComponent<TransformComponent>();
	//TransformComp.Translation = glm::vec3(0.0f, 0.0f, 5.0f);
	//TransformComp.Scale = glm::vec3(10.0f, 10.0f, 10.0f);

	Ref<GameObject> TestGB1 = m_ActiveScene->CreateGameObject();
	TestGB1->AddComponent<StaticMeshComponent>(StaticMeshLibrary::CreateSquareVA(0, 0), CreateRef<Material>(glm::vec3(0.2, 0.3, 0.4), glm::vec3(0.2, 0.3, 0.4), glm::vec4(0.7, 0.6, 0.6, 1.0), 1.0f, ShaderLibrary::GetInstance()->Get("Texture Shader")));
	StaticMeshComponent& MeshComp1 = TestGB1->GetComponent<StaticMeshComponent>();
	MeshComp1.Mat->SetTexture(m_TestTexture);

	Ref<GameObject> TestGB2 = m_ActiveScene->CreateGameObject(TestGB1);
	TestGB2->AddComponent<StaticMeshComponent>(StaticMeshLibrary::CreateSquareVA(0, 0), CreateRef<Material>(glm::vec3(0.2, 0.3, 0.4), glm::vec3(0.2, 0.3, 0.4), glm::vec4(0.7, 0.6, 0.6, 1.0), 1.0f, ShaderLibrary::GetInstance()->Get("Texture Shader")));
	StaticMeshComponent& MeshComp2 = TestGB2->GetComponent<StaticMeshComponent>();
	MeshComp2.Mat->SetTexture(m_TestTexture);
	TransformComponent& Transform2 = TestGB2->GetComponent<TransformComponent>();
	Transform2.Translation = glm::vec3(1, 1, 0);
}

void EditorLayer::OnUpdate(Timestep Ts)
{
	EditorCamera.OnUpdate(Ts);

	if (m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f)
	{
		float AspectRatio = m_ViewportSize.x / m_ViewportSize.y;
		if (AspectRatio != EditorCamera.GetAspect())
		{
			EditorCamera.SetAspect(AspectRatio);
		}
	}
	m_FrameBuffer->Bind();
	m_FrameBuffer->OnUpdate(m_ViewportSize.x, m_ViewportSize.y);
	RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1 });
	RenderCommand::Clear();

	uTime += Ts;

	m_ActiveScene->OnUpdateEditor(Ts, EditorCamera);

	EditorGridShader->Bind();
	EditorGridShader->SetMat4("u_ViewProjection", EditorCamera.GetViewProjection());
	EditorGridShader->SetMat4("u_ViewMat", EditorCamera.GetViewMatrix());
	EditorGridShader->SetMat4("u_ProjMat", EditorCamera.GetProjection());
	EditorGridShader->SetFloat("u_zNear", EditorCamera.GetZNear());
	EditorGridShader->SetFloat("u_zFar", EditorCamera.GetZFar());
	EditorGridVA->Bind();

	RenderCommand::DrawIndexed(EditorGridVA);

	m_FrameBuffer->UnBind();
}

void EditorLayer::OnDetach()
{
}

void EditorLayer::OnImGUIRender()
{

	static bool DockspaceOpen = true;
	static bool OptFullScreenPersistant = true;
	bool OptFullScreen = OptFullScreenPersistant;

	static ImGuiDockNodeFlags DockspaceFlags = ImGuiDockNodeFlags_None;

	ImGuiWindowFlags WindowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	if (OptFullScreen)
	{
		ImGuiViewport* Viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(Viewport->Pos);
		ImGui::SetNextWindowSize(Viewport->Size);
		ImGui::SetNextWindowViewport(Viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		WindowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		WindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}

	if (DockspaceFlags & ImGuiDockNodeFlags_PassthruCentralNode)
		WindowFlags |= ImGuiWindowFlags_NoBackground;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("Mimou Editor", &DockspaceOpen, WindowFlags);
	ImGui::PopStyleVar();

	if (OptFullScreen)
		ImGui::PopStyleVar(2);

	ImGuiIO& IO = ImGui::GetIO();
	if (IO.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID DockspaceID = ImGui::GetID("MimouDockspace");
		ImGui::DockSpace(DockspaceID, ImVec2(0.0f, 0.0f), DockspaceFlags);
	}

	ShowMenuBar();
	ShowViewport();
	ShowSettingPanel();

	for (auto Panels : ActivePanels)
	{
		Panels.second->OnImGUIUpdate();
	}

	ImGui::ShowDemoWindow();
	ImGui::End();
}

void EditorLayer::OnEvent(EventBase& Event)
{

}

void EditorLayer::ShowMenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::MenuItem("(main menu)", NULL, false, false);
			if (ImGui::MenuItem("New")) {}
			if (ImGui::MenuItem("Open", "Ctrl+O")) {}
			if (ImGui::BeginMenu("Open Recent"))
			{
				ImGui::MenuItem("fish_hat.c");
				ImGui::MenuItem("fish_hat.inl");
				ImGui::MenuItem("fish_hat.h");
				if (ImGui::BeginMenu("More.."))
				{
					ImGui::MenuItem("Hello");
					ImGui::MenuItem("Sailor");
					ImGui::EndMenu();
				}
				ImGui::EndMenu();
			}
			if (ImGui::MenuItem("Save", "Ctrl+S")) {}
			if (ImGui::MenuItem("Save As..")) {}

			ImGui::Separator();
			if (ImGui::BeginMenu("Options"))
			{
				static bool enabled = true;
				ImGui::MenuItem("Enabled", "", &enabled);
				ImGui::BeginChild("child", ImVec2(0, 60), true);
				for (int i = 0; i < 10; i++)
					ImGui::Text("Scrolling Text %d", i);
				ImGui::EndChild();
				static float f = 0.5f;
				static int n = 0;
				ImGui::SliderFloat("Value", &f, 0.0f, 1.0f);
				ImGui::InputFloat("Input", &f, 0.1f);
				ImGui::Combo("Combo", &n, "Yes\0No\0Maybe\0\0");
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Colors"))
			{
				float sz = ImGui::GetTextLineHeight();
				for (int i = 0; i < ImGuiCol_COUNT; i++)
				{
					const char* name = ImGui::GetStyleColorName((ImGuiCol)i);
					ImVec2 p = ImGui::GetCursorScreenPos();
					ImGui::GetWindowDrawList()->AddRectFilled(p, ImVec2(p.x + sz, p.y + sz), ImGui::GetColorU32((ImGuiCol)i));
					ImGui::Dummy(ImVec2(sz, sz));
					ImGui::SameLine();
					ImGui::MenuItem(name);
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Options")) // <-- Append!
			{
				static bool b = true;
				ImGui::Checkbox("SomeOption", &b);
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Disabled", false)) // Disabled
			{
				IM_ASSERT(0);
			}
			if (ImGui::MenuItem("Checked", NULL, true)) {}
			ImGui::Separator();
			if (ImGui::MenuItem("Quit", "Alt+F4")) { Application::GetInstance()->Close(); }
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
			if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
			ImGui::Separator();
			if (ImGui::MenuItem("Cut", "CTRL+X")) {}
			if (ImGui::MenuItem("Copy", "CTRL+C")) {}
			if (ImGui::MenuItem("Paste", "CTRL+V")) {}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

void EditorLayer::ShowViewport()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
	ImGui::Begin("Viewport");

	m_IsViewportFocused = ImGui::IsWindowFocused();
	m_IsViewportHovered = ImGui::IsWindowHovered();

	Application::GetInstance()->GetImGuiLayer()->BlockEvents(!m_IsViewportHovered);
	Input::EnableInput(m_IsViewportHovered);
	
	ImVec2 ViewportPanelSize = ImGui::GetContentRegionAvail();
	m_ViewportSize = { ViewportPanelSize.x, ViewportPanelSize.y };
	ImGui::Image((void*)(intptr_t)m_FrameBuffer->GetColorAttachmentTexID(), ImVec2(m_ViewportSize.x, m_ViewportSize.y), ImVec2(0, 1), ImVec2(1, 0));
	//ImGui::Image((void*)(intptr_t)m_FrameBuffer->GetDepthStencilAttachTexID(), ImVec2(m_ViewportSize.x, m_ViewportSize.y), ImVec2(0, 1), ImVec2(1, 0));

	//ImGui::Image((void*)(intptr_t)m_TestTexture->GetRendererID(), ImVec2(m_ViewportSize.x, m_ViewportSize.y), ImVec2(0, 1), ImVec2(1, 0));
	ImGui::End();
	ImGui::PopStyleVar();
}

void EditorLayer::ShowSettingPanel()
{
	bool IsPOpen = false;
	ImGui::Begin("Setting" , &IsPOpen, ImGuiWindowFlags_HorizontalScrollbar);

	ImGui::ColorEdit3("Test Color section", TmpColor, ImGuiColorEditFlags_InputRGB);

	ImGui::Separator();
	
	ImGui::End();
}

void EditorLayer::ShowPanel(PanelType Type, const std::string& PanelName)
{
	if (ActivePanels.contains(Type))
	{
		return;
	}
	if (CachedPanels.contains(Type))
	{
		ActivePanels.emplace(std::pair<PanelType, Ref<Panel>>(Type, CachedPanels[Type]));
		CachedPanels.erase(Type);
	}
	else
	{
		Ref<Panel> NewPanel = Panel::CreatePanel(Type, PanelName, m_ActiveScene);
		ActivePanels.emplace(std::pair<PanelType, Ref<Panel>>(Type, NewPanel));
	}
}
