#include "ShaderExamples.h"

ShaderEgLayer::ShaderEgLayer()
	: m_CameraController(glm::radians(70.0f), 3.0f/2.0f)
{
	
	//TestSun();
	float Width = (float)Application::GetInstance()->GetWindow().GetWidth();
	float Height = (float)Application::GetInstance()->GetWindow().GetHeight();
	m_CameraController.SetAspect(Width / Height);

	DirectionalLight = CreateRef<Light>(glm::vec3(), glm::vec3(45.0, 135.0, 0), glm::vec3(0.7, 0.6, 0.6), 1.0f);
	MovingLight = CreateRef<Light>(glm::vec3(), glm::vec3(0, 180, 0), glm::vec3(0.5, 0.4, 0.4), 1.0f);

	RenderCommand::EnableDepthTest();
	RenderCommand::EnableBlend();
	RenderCommand::ClearDepth();

	//SphereShader = Shader::Create("Assets/Shaders/SphereShader.glsl");

	//Ref<StaticMesh> SphereMesh = StaticMeshLibrary::CreateSphere(32, 16);
	//SphereVertices = VertexArray::Create();

	//BufferLayout Layout =
	//{
	//	{ "a_Position", ShaderDataType::Float3 },
	//	{ "a_Normal", ShaderDataType::Float3 }
	//};

	//float* V_Arr = SphereMesh->GetVertices();
	//Ref<VertexBuffer> VertexBuffer = VertexBuffer::Create(V_Arr, SphereMesh->GetSize() * sizeof(float));
	//VertexBuffer->SetLayout(Layout);
	//SphereVertices->AddVertexBuffer(VertexBuffer);
	Ref<Shader> LambertShader = Shader::Create("Assets/Shaders/LambertShader.glsl");
	Ref<Material> LambertMat = CreateRef<Material>(glm::vec3(0.2, 0.3, 0.4), glm::vec3(0.2, 0.3, 0.4), glm::vec4(0.7, 0.6, 0.6, 1.0), 1.0f, LambertShader);
	//SphereMesh = StaticMeshLibrary::CreateSphere(32, 16);
	//SphereMesh->SetMaterial(LambertMat);
	Renderer::AddLight(DirectionalLight);
	Renderer::AddLight(MovingLight);

	Ref<GameObject> SphereObject = CreateRef<GameObject>();
	Ref<StaticMeshComponent> SMComp = CreateRef<StaticMeshComponent>(StaticMeshLibrary::CreateSphere(32, 16));
	SMComp->GetStaticMesh()->SetMaterial(LambertMat);
	SphereObject->AddComponent(SMComp);
	SphereObject->m_Transform.SetPosition(glm::vec3(-3, 0, 0));
	GameObjects.push_back(SphereObject);

	Ref<GameObject> SphereObject1 = CreateRef<GameObject>();
	Ref<Shader> PhongShader = Shader::Create("Assets/Shaders/PhongShader.glsl");
	Ref<Material> PhongMat = CreateRef<Material>(glm::vec3(0.2, 0.2, 0.2), glm::vec3(1, 1, 1), glm::vec4(0.9, 0.9, 0.9, 10.0), 1.0f, PhongShader);
	Ref<StaticMeshComponent> SMComp1 = CreateRef<StaticMeshComponent>(StaticMeshLibrary::CreateSphere(32, 16));
	SMComp1->GetStaticMesh()->SetMaterial(PhongMat);
	SphereObject1->AddComponent(SMComp1);
	SphereObject1->m_Transform.SetPosition(glm::vec3(0, 0, 0));
	GameObjects.push_back(SphereObject1);

	Ref<GameObject> SphereEar1 = CreateRef<GameObject>();
	Ref<Material> PhongMat1 = CreateRef<Material>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(0.1, 0.1, 0.1, 10.0), 1.0f, PhongShader);
	Ref<StaticMeshComponent> SMComp2 = CreateRef<StaticMeshComponent>(StaticMeshLibrary::CreateSphere(32, 16));
	SMComp2->GetStaticMesh()->SetMaterial(PhongMat1);
	SphereEar1->AddComponent(SMComp2);
	SphereEar1->m_Transform.SetPosition(glm::vec3(1, 1, 0));
	SphereEar1->m_Transform.SetScale(glm::vec3(1, 1, 0.4));
	GameObjects.push_back(SphereEar1);
	SphereObject1->AddChild(SphereEar1.get());

	Ref<GameObject> SphereObject2 = CreateRef<GameObject>();
	Ref<Shader> BlinnPhongShader = Shader::Create("Assets/Shaders/BlinnPhongShader.glsl");
	Ref<Material> BlinnPhongMat = CreateRef<Material>(glm::vec3(0.2, 0.2, 0.2), glm::vec3(1, 1, 1), glm::vec4(0.9, 0.9, 0.9, 10.0), 1.0f, BlinnPhongShader);
	Ref<StaticMeshComponent> SMComp3 = CreateRef<StaticMeshComponent>(StaticMeshLibrary::CreateSphere(32, 16));
	SMComp3->GetStaticMesh()->SetMaterial(BlinnPhongMat);
	SphereObject2->AddComponent(SMComp3);
	SphereObject2->m_Transform.SetPosition(glm::vec3(4, 1, 0));
	GameObjects.push_back(SphereObject2);

	Ref<GameObject> SquareObject = CreateRef<GameObject>();

	Ref<Shader> TextureShader = Shader::Create("Assets/Shaders/Texture.glsl");
	Ref<Texture> GridTexture = Texture2D::Create("Assets/Textures/Checkerboard.png");
	Ref<Material> TextureMat = CreateRef<Material>(glm::vec3(0.2, 0.3, 0.4), glm::vec3(0.2, 0.3, 0.4), glm::vec4(0.7, 0.6, 0.6, 1.0), 1.0f, TextureShader);
	TextureMat->SetTexture(GridTexture);
	Ref<StaticMeshComponent> SMComp4 = CreateRef<StaticMeshComponent>(StaticMeshLibrary::CreateSquare(2, 1));
	SMComp4->GetStaticMesh()->SetMaterial(TextureMat);
	SquareObject->AddComponent(SMComp4);
	//SquareObject->m_Transform.SetScale(glm::vec3(100, 100, 1));
	SquareObject->m_Transform.SetRotation(glm::vec3(0, 0, 0));
	SquareObject->m_Transform.SetPosition(glm::vec3(0, -8, 0));
	GameObjects.push_back(SquareObject);

	Ref<GameObject> CubeObject = CreateRef<GameObject>();
	Ref<Texture> GridTexture1 = Texture2D::Create("Assets/Textures/duxin.jpg");
	Ref<Material> TextureMat1 = CreateRef<Material>(glm::vec3(0.2, 0.3, 0.4), glm::vec3(0.2, 0.3, 0.4), glm::vec4(0.7, 0.6, 0.6, 1.0), 1.0f, TextureShader);
	TextureMat1->SetTexture(GridTexture1);
	Ref<StaticMeshComponent> SMComp5 = CreateRef<StaticMeshComponent>(StaticMeshLibrary::CreateCube());
	SMComp5->GetStaticMesh()->SetMaterial(TextureMat1);
	CubeObject->AddComponent(SMComp5);
	CubeObject->m_Transform.SetPosition(glm::vec3(0, -4, 0));
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

ShaderEgLayer::~ShaderEgLayer()
{
}

void ShaderEgLayer::OnUpdate(Timestep Ts)
{
	m_CameraController.OnUpdate(Ts);

	Renderer::BeginScene(m_CameraController.GetCamera());

	RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1 });
	RenderCommand::Clear();

	//Renderer::Submit(SunVertices, SunShader);
	//Renderer::SubmitArrays(SphereVertices, SphereShader);
	//Renderer::SubmitArrays(SphereMesh->GetVertexArray(), SphereMesh->GetMaterial(), DirectionalLight);
	MovingLight->m_Transform.SetYaw(MovingLight->m_Transform.GetYaw() + Ts.GetSecond() * 100);

	GameObjects[0]->m_Transform.SetPosition(glm::vec3(-3.0f, 3.0f * glm::abs(glm::sin(uTime)), 0.0f));
	GameObjects[1]->m_Transform.SetPosition(glm::vec3(0.0f, 4.0f * glm::abs(glm::cos(uTime)), 0.0f));
	GameObjects[3]->m_Transform.SetPosition(glm::vec3(4.0f, 3.0f * glm::abs(glm::sin(uTime)), 0.0f));
	//GameObjects[4]->m_Transform.SetRotation(glm::vec3(0.0f, 50.0f * uTime, 0.0f));
	GameObjects[5]->m_Transform.SetRotation(glm::vec3(0.0f, 50.0f * uTime, 0.0f));

	uTime += Ts;

	for (Ref<GameObject> GameObject : GameObjects)
	{
		GameObject->OnUpdate(Ts);
	}

	//Renderer::Submit(EditorGridVA, EditorGridShader);
	EditorGridShader->Bind();
	EditorGridShader->SetMat4("u_ViewProjection", m_CameraController.GetCamera().GetViewProjectionMatrix());
	EditorGridShader->SetMat4("u_ViewMat", m_CameraController.GetCamera().GetViewMatrix());
	EditorGridShader->SetMat4("u_ProjMat", m_CameraController.GetCamera().GetProjectionMatrix());
	//EditorGridShader->SetMat4("u_TransformMatrix", Transfrom);
	EditorGridVA->Bind();

	RenderCommand::DrawIndexed(EditorGridVA);

	Renderer::EndScene();
}

void ShaderEgLayer::OnAttach()
{
}

void ShaderEgLayer::OnDetach()
{
}

void ShaderEgLayer::OnImGUIRender()
{
}

void ShaderEgLayer::OnEvent(EventBase& Event)
{
	m_CameraController.OnEvent(Event);
}

void ShaderEgLayer::TestSun()
{
	SunShader = Shader::Create("Assets/Shaders/SunShader.glsl");

	SunVertices = VertexArray::Create();

	float Vertices[3 * 4] =
	{
		-1, 1, 0,
		1, 1, 0,
		-1, -1, 0,
		1, -1, 0
	};
	BufferLayout Layout =
	{
		{ "a_Position", ShaderDataType::Float3 }
	};
	uint32_t Indices[6] =
	{
		0, 1, 2, 2, 3, 1
	};

	Ref<VertexBuffer> VertexBuffer = VertexBuffer::Create(Vertices, sizeof(Vertices));
	VertexBuffer->SetLayout(Layout);

	Ref<IndexBuffer> IndexBuffer = IndexBuffer::Create(Indices, 6);
	SunVertices->AddVertexBuffer(VertexBuffer);

	SunVertices->AddIndexBuffer(IndexBuffer);
}
