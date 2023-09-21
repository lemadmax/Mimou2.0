#include "ShaderExamples.h"

ShaderEgLayer::ShaderEgLayer()
	: m_CameraController(glm::radians(70.0f), 3.0f/2.0f)
{
	//TestSun();
	float Width = (float)Application::GetInstance()->GetWindow().GetWidth();
	float Height = (float)Application::GetInstance()->GetWindow().GetHeight();
	m_CameraController.SetAspect(Width / Height);

	DirectionalLight = CreateRef<Light>(glm::vec3(), glm::vec3(0.7, 0.6, 0.6), glm::vec3(1.0, 1.0, 1.0), 1.0f);

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
	SphereMesh = StaticMeshLibrary::CreateSphere(32, 16);
	SphereMesh->SetMaterial(LambertMat);
}

ShaderEgLayer::~ShaderEgLayer()
{
}

void ShaderEgLayer::OnUpdate(Timestep Ts)
{
	m_CameraController.OnUpdate(Ts);

	Renderer::BeginScene(m_CameraController.GetCamera());

	RenderCommand::SetClearColor({ 0.4f, 0.4f, 0.4f, 1 });
	RenderCommand::Clear();
	//Renderer::Submit(SunVertices, SunShader);
	//Renderer::SubmitArrays(SphereVertices, SphereShader);
	Renderer::SubmitArrays(SphereMesh->GetVertexArray(), SphereMesh->GetMaterial(), DirectionalLight);

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
