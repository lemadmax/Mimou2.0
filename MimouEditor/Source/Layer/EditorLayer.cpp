#include "EditorLayer.h"


namespace Mimou
{
	EditorLayer* EditorLayer::s_Instance = nullptr;

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

		ImGuiIO& IO = ImGui::GetIO();
		ImFont* Roboto = IO.Fonts->AddFontFromFileTTF("Assets/Fonts/Roboto/Roboto-Light.ttf", 18.0f);
		IO.FontDefault = Roboto;

		ImGuiStyle* style = &ImGui::GetStyle();
		ImVec4* colors = style->Colors;

		colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
		colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.29f, 0.48f, 0.54f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.29f, 0.48f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
		colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.20f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
		colors[ImGuiCol_TabHovered] = colors[ImGuiCol_HeaderHovered];
		colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
		colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);   // Prefer using Alpha=1.0 here
		colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);   // Prefer using Alpha=1.0 here
		colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
		colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
	}

	EditorLayer::~EditorLayer()
	{

	}

	EditorLayer* EditorLayer::GetInstance()
	{
		if (!s_Instance)
		{
			s_Instance = new EditorLayer();
		}
		return s_Instance;
	}

	void EditorLayer::OnAttach()
	{
		uint32_t Width = Application::GetInstance()->GetWindow().GetWidth();
		uint32_t Height = Application::GetInstance()->GetWindow().GetHeight();
		m_FrameBuffer = FrameBuffer::Create({ Width , Height });

		m_ActiveScene = CreateRef<Scene>("Editor Test Scene");

		//m_TestTexture = Texture2D::Create("Assets/Textures/duxin.jpg");

		ShowPanel(PanelType::SceneHierarchyPanel, "Scene");
		ShowPanel(PanelType::PropertiesPanel, "Properties");

		//Ref<GameObject> Camera1 = Scene::CreateGameObject(m_ActiveScene, "Camera 1");
		//Camera1->AddComponent<CameraComponent>(CreateRef<SceneCamera>());
		//Ref<GameObject> Camera2 = Scene::CreateGameObject(m_ActiveScene, "Camera 2");
		//Camera2->AddComponent<CameraComponent>(CreateRef<SceneCamera>());

		//Ref<GameObject> Light1 = Scene::CreateGameObject(m_ActiveScene, "Light 1");
		//Light1->AddComponent<LightComponent>(1.0f, true);
		//TransformComponent& TransformLight1 = Light1->GetComponent<TransformComponent>();
		//TransformLight1.Rotation = glm::vec3(0.0f, glm::radians(180.0f), 0.0f);
		
		//Ref<GameObject> TestGB0 = m_ActiveScene->CreateGameObject("Square 1");
		//TestGB0->AddComponent<StaticMeshComponent>(StaticMeshLibrary::CreateSquareVA(2, 0), CreateRef<Material>(glm::vec3(0.2, 0.3, 0.4), glm::vec3(0.2, 0.3, 0.4), glm::vec4(0.7, 0.6, 0.6, 1.0), 1.0f, ShaderLibrary::GetInstance()->Get("Texture Shader")));
		//StaticMeshComponent& MeshComp = TestGB0->GetComponent<StaticMeshComponent>();
		//MeshComp.Mat->SetTexture(m_TestTexture);

		//Ref<GameObject> TestGB1 = m_ActiveScene->CreateGameObject("Square 2");
		//TestGB1->AddComponent<StaticMeshComponent>(StaticMeshLibrary::CreateSquareVA(0, 0), CreateRef<Material>(glm::vec3(0.2, 0.3, 0.4), glm::vec3(0.2, 0.3, 0.4), glm::vec4(0.7, 0.6, 0.6, 1.0), 1.0f, ShaderLibrary::GetInstance()->Get("Texture Shader")));
		//StaticMeshComponent& MeshComp1 = TestGB1->GetComponent<StaticMeshComponent>();
		//MeshComp1.Mat->SetTexture(m_TestTexture);

		//Ref<GameObject> TestGB2 = m_ActiveScene->CreateGameObject("Square 3", TestGB1);
		//TestGB2->AddComponent<StaticMeshComponent>(StaticMeshLibrary::CreateSquareVA(0, 0), CreateRef<Material>(glm::vec3(0.2, 0.3, 0.4), glm::vec3(0.2, 0.3, 0.4), glm::vec4(0.7, 0.6, 0.6, 1.0), 1.0f, ShaderLibrary::GetInstance()->Get("Texture Shader")));
		//StaticMeshComponent& MeshComp2 = TestGB2->GetComponent<StaticMeshComponent>();
		//MeshComp2.Mat->SetTexture(m_TestTexture);
		//TransformComponent& Transform2 = TestGB2->GetComponent<TransformComponent>();
		//Transform2.Translation = glm::vec3(1, 1, 0);

		//Ref<GameObject> Cube1 = Scene::CreateGameObject(m_ActiveScene, "Cube 1", nullptr);
		//Cube1->AddComponent<StaticMeshComponent>("Cube");
		
		//Ref<GameObject> Sphere1 = m_ActiveScene->CreateGameObject("Sphere 1");
		//Sphere1->AddComponent<StaticMeshComponent>(StaticMeshLibrary::CreateSphereVA(50, 100), CreateRef<Material>(glm::vec3(0.2, 0.3, 0.4), glm::vec3(0.2, 0.3, 0.4), glm::vec4(0.7, 0.6, 0.6, 1.0), 1.0f, ShaderLibrary::GetInstance()->Get("Phong Shader")));
		//TransformComponent& Transform1 = Sphere1->GetComponent<TransformComponent>();
		//Transform1.Translation = glm::vec3(3, 0, 0);

		//Ref<GameObject> Sphere2 = m_ActiveScene->CreateGameObject("Sphere 2");
		//Sphere2->AddComponent<StaticMeshComponent>(StaticMeshLibrary::CreateSphereVA(50, 100), CreateRef<Material>(glm::vec3(0.2, 0.3, 0.4), glm::vec3(0.2, 0.3, 0.4), glm::vec4(0.7, 0.6, 0.6, 1.0), 1.0f, ShaderLibrary::GetInstance()->Get("Lambert Shader")));
		//TransformComponent& Transform2 = Sphere2->GetComponent<TransformComponent>();
		//Transform2.Translation = glm::vec3(-3, 0, 0);

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
		Ref<GameObject> PrimaryCameraGB = m_ActiveScene->GetPrimiaryCamera();
		if (PrimaryCameraGB)
		{
			CameraComponent CameraComp = PrimaryCameraGB->GetComponent<CameraComponent>();
			TransformComponent TransformComp = PrimaryCameraGB->GetComponent<TransformComponent>();
			glm::mat4 ProjectMatrix = CameraComp.Camera->GetProjection();
			glm::mat4 ViewMatrix = glm::inverse(TransformComp.GetTransform());
			glm::mat4 ViewProjection = ProjectMatrix * ViewMatrix;
			EditorGridShader->SetMat4("u_ViewProjection", ViewProjection);
			EditorGridShader->SetMat4("u_ViewMat", ViewMatrix);
			EditorGridShader->SetMat4("u_ProjMat", ProjectMatrix);
			EditorGridShader->SetFloat("u_zNear", CameraComp.Camera->GetZNear());
			EditorGridShader->SetFloat("u_zFar", CameraComp.Camera->GetZFar());
		}
		else
		{
			EditorGridShader->SetMat4("u_ViewProjection", EditorCamera.GetViewProjection());
			EditorGridShader->SetMat4("u_ViewMat", EditorCamera.GetViewMatrix());
			EditorGridShader->SetMat4("u_ProjMat", EditorCamera.GetProjection());
			EditorGridShader->SetFloat("u_zNear", EditorCamera.GetZNear());
			EditorGridShader->SetFloat("u_zFar", EditorCamera.GetZFar());
		}

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
		//ShowSettingPanel();

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
				//if (ImGui::BeginMenu("Open Recent"))
				//{
				//	ImGui::MenuItem("fish_hat.c");
				//	ImGui::MenuItem("fish_hat.inl");
				//	ImGui::MenuItem("fish_hat.h");
				//	if (ImGui::BeginMenu("More.."))
				//	{
				//		ImGui::MenuItem("Hello");
				//		ImGui::MenuItem("Sailor");
				//		ImGui::EndMenu();
				//	}
				//	ImGui::EndMenu();
				//}
				if (ImGui::MenuItem("Save", "Ctrl+S")) 
				{
					if (m_ActiveScene)
					{
						SceneSerializer::Get()->SerializeScene(m_ActiveScene, "Assets/Scene/Example.mimou");
					}
				}
				if (ImGui::MenuItem("Open..."))
				{
					std::string FileName = FileDialog::MEGetOpenFileName("Mimou File (*.mimou)\0*.mimou\0");
					if (!FileName.empty())
					{
						Ref<Scene> Loaded = SceneSerializer::Get()->DeserializeScene(FileName);
						if (Loaded)
						{
							m_ActiveScene = Loaded;
						}
					}
				}
				if (ImGui::MenuItem("Save As...")) 
				{
					std::string FileName = FileDialog::MEGetSaveFileName("Mimou File (*.mimou)\0*.mimou\0");
					if (!FileName.empty())
					{
						SceneSerializer::Get()->SerializeScene(m_ActiveScene, FileName);
					}
				}


				if (ImGui::MenuItem("Test reload shader"))
				{
					ShaderLibrary::GetInstance()->Reload("Default", "Assets/Shaders/Default.glsl");
				}

			//	ImGui::Separator();
			//	if (ImGui::BeginMenu("Options"))
			//	{
			//		static bool enabled = true;
			//		ImGui::MenuItem("Enabled", "", &enabled);
			//		ImGui::BeginChild("child", ImVec2(0, 60), true);
			//		for (int i = 0; i < 10; i++)
			//			ImGui::Text("Scrolling Text %d", i);
			//		ImGui::EndChild();
			//		static float f = 0.5f;
			//		static int n = 0;
			//		ImGui::SliderFloat("Value", &f, 0.0f, 1.0f);
			//		ImGui::InputFloat("Input", &f, 0.1f);
			//		ImGui::Combo("Combo", &n, "Yes\0No\0Maybe\0\0");
			//		ImGui::EndMenu();
			//	}

			//	if (ImGui::BeginMenu("Colors"))
			//	{
			//		float sz = ImGui::GetTextLineHeight();
			//		for (int i = 0; i < ImGuiCol_COUNT; i++)
			//		{
			//			const char* name = ImGui::GetStyleColorName((ImGuiCol)i);
			//			ImVec2 p = ImGui::GetCursorScreenPos();
			//			ImGui::GetWindowDrawList()->AddRectFilled(p, ImVec2(p.x + sz, p.y + sz), ImGui::GetColorU32((ImGuiCol)i));
			//			ImGui::Dummy(ImVec2(sz, sz));
			//			ImGui::SameLine();
			//			ImGui::MenuItem(name);
			//		}
			//		ImGui::EndMenu();
			//	}

			//	if (ImGui::BeginMenu("Options")) // <-- Append!
			//	{
			//		static bool b = true;
			//		ImGui::Checkbox("SomeOption", &b);
			//		ImGui::EndMenu();
			//	}

			//	if (ImGui::BeginMenu("Disabled", false)) // Disabled
			//	{
			//		IM_ASSERT(0);
			//	}
				if (ImGui::MenuItem("Checked", NULL, true)) {}
				ImGui::Separator();
				if (ImGui::MenuItem("Quit", "Alt+F4")) { Application::GetInstance()->Close(); }
				ImGui::EndMenu();
			}
			//if (ImGui::BeginMenu("Edit"))
			//{
			//	if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
			//	if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
			//	ImGui::Separator();
			//	if (ImGui::MenuItem("Cut", "CTRL+X")) {}
			//	if (ImGui::MenuItem("Copy", "CTRL+C")) {}
			//	if (ImGui::MenuItem("Paste", "CTRL+V")) {}
			//	ImGui::EndMenu();
			//}
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
		ImGui::Begin("Setting", &IsPOpen, ImGuiWindowFlags_HorizontalScrollbar);

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
			Ref<Panel> NewPanel = Panel::CreatePanel(Type, PanelName);
			ActivePanels.emplace(std::pair<PanelType, Ref<Panel>>(Type, NewPanel));
		}
	}

	bool EditorLayer::IsPanelOpen(PanelType Type)
	{
		return ActivePanels.contains(Type);
	}

	Ref<Panel> EditorLayer::GetPanel(PanelType Type)
	{
		return ActivePanels[Type];
	}


}