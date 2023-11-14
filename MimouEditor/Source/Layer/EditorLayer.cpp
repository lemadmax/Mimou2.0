#include "EditorLayer.h"

EditorLayer::EditorLayer()
	: m_CameraController(glm::radians(70.0f), 3.0f/2.0f)
{
	
	//TestSun();
	float Width = (float)Application::GetInstance()->GetWindow().GetWidth();
	float Height = (float)Application::GetInstance()->GetWindow().GetHeight();
	m_CameraController.SetAspect(Width / Height);

	DirectionalLight = CreateRef<Light>(glm::vec3(), glm::vec3(45.0, 135.0, 0), glm::vec3(0.7, 0.6, 0.6), 1.0f);
	MovingLight = CreateRef<Light>(glm::vec3(), glm::vec3(0, 180, 0), glm::vec3(0.5, 0.4, 0.4), 1.0f);
	Renderer::AddLight(DirectionalLight);
	Renderer::AddLight(MovingLight);

	RenderCommand::EnableDepthTest();
	RenderCommand::EnableBlend();
	RenderCommand::ClearDepth();

	m_TestTexture = Texture2D::Create("Assets/Textures/duxin.jpg");

	Ref<Shader> TextureShader = Shader::Create("Assets/Shaders/Texture.glsl");

	Ref<GameObject> CubeObject = CreateRef<GameObject>();
	Ref<Texture> GridTexture1 = Texture2D::Create("Assets/Textures/duxin.jpg");
	Ref<Material> TextureMat1 = CreateRef<Material>(glm::vec3(0.2, 0.3, 0.4), glm::vec3(0.2, 0.3, 0.4), glm::vec4(0.7, 0.6, 0.6, 1.0), 1.0f, TextureShader);
	TextureMat1->SetTexture(GridTexture1);
	Ref<StaticMeshComponent> SMComp5 = CreateRef<StaticMeshComponent>(StaticMeshLibrary::CreateCube());
	SMComp5->GetStaticMesh()->SetMaterial(TextureMat1);
	CubeObject->AddComponent(SMComp5);
	CubeObject->m_Transform.SetPosition(glm::vec3(0, 3, 0));
	GameObjects.push_back(CubeObject);

	EditorGridShader = Shader::Create("Assets/Shaders/EditorGrid.glsl"); 
	EditorGridVA = VertexArray::Create();
	uint32_t Indices[6] =
	{
		0, 1, 2, 1, 0, 3
	};
	Ref<IndexBuffer> IndexBuffer;
	IndexBuffer = IndexBuffer::Create(Indices, 6);
	EditorGridVA->AddIndexBuffer(IndexBuffer);

}

EditorLayer::~EditorLayer()
{
}

void EditorLayer::OnUpdate(Timestep Ts)
{
	m_CameraController.OnUpdate(Ts);

	Renderer::BeginScene(m_CameraController.GetCamera());

	if (m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f)
	{
		float AspectRatio = m_ViewportSize.x / m_ViewportSize.y;
		if (AspectRatio != m_CameraController.GetAspect())
		{
			m_CameraController.SetAspect(AspectRatio);
		}
	}
	m_FrameBuffer->Bind();
	m_FrameBuffer->OnUpdate(m_ViewportSize.x, m_ViewportSize.y);
	RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1 });
	RenderCommand::Clear();

	MovingLight->m_Transform.SetYaw(MovingLight->m_Transform.GetYaw() + Ts.GetSecond() * 100);

	GameObjects[0]->m_Transform.SetRotation(glm::vec3(0.0f, 50.0f * uTime, 0.0f));

	uTime += Ts;

	for (Ref<GameObject> GameObject : GameObjects)
	{
		GameObject->OnUpdate(Ts);
	}

	EditorGridShader->Bind();
	EditorGridShader->SetMat4("u_ViewProjection", m_CameraController.GetCamera().GetViewProjectionMatrix());
	EditorGridShader->SetMat4("u_ViewMat", m_CameraController.GetCamera().GetViewMatrix());
	EditorGridShader->SetMat4("u_ProjMat", m_CameraController.GetCamera().GetProjectionMatrix());
	EditorGridShader->SetFloat("u_zNear", m_CameraController.GetZNear());
	EditorGridShader->SetFloat("u_zFar", m_CameraController.GetZFar());
	EditorGridVA->Bind();

	RenderCommand::DrawIndexed(EditorGridVA);

	Renderer::EndScene();

	m_FrameBuffer->UnBind();
}

void EditorLayer::OnAttach()
{
	uint32_t Width = Application::GetInstance()->GetWindow().GetWidth();
	uint32_t Height = Application::GetInstance()->GetWindow().GetHeight();
	m_FrameBuffer = FrameBuffer::Create({ Width , Height });
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

	ImGui::ShowDemoWindow();
	ImGui::End();
}

void EditorLayer::OnEvent(EventBase& Event)
{
	m_CameraController.OnEvent(Event);
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
	ImGui::Begin("Viewport");

	ImVec2 ViewportPanelSize = ImGui::GetContentRegionAvail();
	m_ViewportSize = { ViewportPanelSize.x, ViewportPanelSize.y };
	ImGui::Image((void*)(intptr_t)m_FrameBuffer->GetColorAttachmentTexID(), ImVec2(m_ViewportSize.x, m_ViewportSize.y), ImVec2(0, 1), ImVec2(1, 0));
	//ImGui::Image((void*)(intptr_t)m_TestTexture->GetRendererID(), ImVec2(m_ViewportSize.x, m_ViewportSize.y), ImVec2(0, 1), ImVec2(1, 0));
	ImGui::End();
}
