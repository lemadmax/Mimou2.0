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

	struct TagComponent
	{
		std::string Tag = "GameObject";

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& InTag)
			: Tag(InTag) {}
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

	struct CameraComponent
	{
		Ref<SceneCamera> Camera;
		bool IsPrimary = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
		CameraComponent(Ref<SceneCamera> InCamera)
			: Camera(InCamera) {}
	};

	struct LightComponent
	{
		glm::vec3 Color = { 1.0f, 1.0f, 1.0f };
		float Intensity = 1.0f;
		bool IsDirectional = true;
		bool IsOn = true;

		LightComponent() = default;
		LightComponent(const LightComponent&) = default;
		LightComponent(const glm::vec3& InColor, float InIntensity, bool InIsDir)
			: Color(InColor), Intensity(InIntensity), IsDirectional(InIsDir) {}
	};
}