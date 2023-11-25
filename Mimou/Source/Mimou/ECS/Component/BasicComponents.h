#pragma once
#include "Mimou/Core.h"
#include "Mimou/Renderer/VertexArray.h"
#include "Mimou/Renderer/Material/Material.h"
#include "Mimou/Renderer/Camera/Camera.h"

#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"

namespace Mimou
{
	struct IDComponent
	{

	};

	struct TransformComponent
	{
		glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3& InTranslation)
			: Translation(InTranslation) {}

		glm::mat4 GetTransform() const
		{
			glm::mat4 RotationMat = glm::toMat4(glm::quat(Rotation));

			return glm::translate(glm::mat4(1.0f), Translation) * RotationMat * glm::scale(glm::mat4(1.0f), Scale);
		}
	};

	struct StaticMeshComponent
	{
		Ref<Mimou::VertexArray> VertexArray;
		Ref<Mimou::Material> Mat;

		StaticMeshComponent() = default;
		StaticMeshComponent(const StaticMeshComponent&) = default;
		StaticMeshComponent(Ref<Mimou::VertexArray> InVertexArray, Ref<Mimou::Material> InMat)
			: VertexArray(InVertexArray), Mat(InMat) {}
	};

	struct DirectionalLightComponent
	{
		glm::vec3 Color = { 1.0f, 1.0f, 1.0f };
		glm::vec3 Direction = { 1.0f, 1.0f, 1.0f };
		float Intensity = 1.0f;
		bool bIsOn = true;

		DirectionalLightComponent() = default;
		DirectionalLightComponent(const DirectionalLightComponent&) = default;
		DirectionalLightComponent(const glm::vec3& InColor, const glm::vec3& InDirection, float InIntensity = 1.0)
			: Color(InColor), Direction(InDirection), Intensity(InIntensity) {}
	};

	struct CameraComponent
	{
		Ref<Mimou::Camera> Camera;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
		CameraComponent(Ref<Mimou::Camera> InCamera)
			: Camera(InCamera) {}
	};
}