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
		glm::vec3 Scale = { 0.0f, 0.0f, 0.0f };

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

	struct SStaticMeshComponent
	{
		Ref<Mimou::VertexArray> VertexArray;
		Ref<Material> Material;

		SStaticMeshComponent() = default;
		SStaticMeshComponent(const SStaticMeshComponent&) = default;
		SStaticMeshComponent(Ref<Mimou::VertexArray> InVertexArray, Ref<Mimou::Material> InMaterial)
			: VertexArray(InVertexArray), Material(InMaterial) {}
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