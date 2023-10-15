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

	uTime += Ts;

	for (Ref<GameObject> GameObject : GameObjects)
	{
		GameObject->OnUpdate(Ts);
	}

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
