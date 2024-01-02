#pragma once
#include "Mimou/Core.h"
#include "Mimou/Renderer/VertexArray.h"
#include "Mimou/Renderer/Material/Material.h"
#include "Mimou/Renderer/Camera/SceneCamera.h"
#include "Mimou/ECS/MimouObject.h"

#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"

namespace Mimou
{
	struct IDComponent
	{

	};

	struct TagComponent : public MEObject
	{
		DECLARE_ME_STRUCT(TagComponent)
		std::string Tag = "GameObject";

		TagComponent();
	};

	struct TransformComponent
	{
		glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3& InTranslation, const glm::vec3& InRot, const glm::vec3& InScale)
			: Translation(InTranslation), Rotation(InRot), Scale(InScale) {}

		glm::mat4 GetTransform() const
		{
			glm::mat4 RotationMat = glm::toMat4(glm::quat(Rotation));

			return glm::translate(glm::mat4(1.0f), Translation) * RotationMat * glm::scale(glm::mat4(1.0f), Scale);
		}

		glm::quat Quat() const
		{
			return glm::quat(Rotation);
		}

		glm::vec3 GetDirection() const
		{
			glm::vec3 Direction = glm::normalize(glm::quat(Rotation) * glm::vec3(0.0f, 0.0f, 1.0f));
			return Direction;
		}
	};

#define MAX_MATSLOT_NUM 8

	struct StaticMeshComponent
	{
		std::string AssetName = "Cube";
		std::vector<Ref<Material>> MaterialSlots;

		StaticMeshComponent()
		{
			MaterialSlots.push_back(MaterialLibrary::Get()->GetMaterial("DefaultMat"));
		}
		StaticMeshComponent(const StaticMeshComponent&) = default;
		StaticMeshComponent(const std::string& InAssetName)
			: AssetName(InAssetName) 
		{
			MaterialSlots.push_back(MaterialLibrary::Get()->GetMaterial("DefaultMat"));
		}
	};

	struct CameraComponent
	{
		Ref<SceneCamera> Camera;
		bool IsPrimary = false;

		CameraComponent()
		{
			Camera = CreateRef<SceneCamera>();
		}
		CameraComponent(const CameraComponent&) = default;
		CameraComponent(Ref<SceneCamera> InCamera)
			: Camera(InCamera) {}
	};

	struct LightComponent
	{
		glm::vec3 Color = { 1.0, 1.0, 1.0 };
		float Intensity = 1.0f;
		bool IsDirectional = true;
		bool IsOn = true;

		LightComponent() = default;
		LightComponent(const LightComponent&) = default;
		LightComponent(float InIntensity, bool InIsDir, bool InIsOn = true)
			: Intensity(InIntensity), IsDirectional(InIsDir), IsOn(InIsOn) {}
	};
}