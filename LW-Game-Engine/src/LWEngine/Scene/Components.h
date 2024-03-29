#pragma once

#include "LWEngine/Scene/SceneCamera.h"
#include "LWEngine/Renderer/Texture.h"
#include "LWEngine/Core/UUID.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace LWEngine {

	struct IDComponent
	{
		UUID ID;

		IDComponent() = default;
		IDComponent(const IDComponent&) = default;

	};

	struct TagComponent
	{
		std::string Tag;
		std::string Name = "Tag Component";
		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& Tag)
			: Tag(Tag) {}

	};

	struct TransformComponent
	{
		glm::vec3 Translation = { 0.0f,0.0f,0.0f };
		glm::vec3 Rotation = { 0.0f,0.0f,0.0f };
		glm::vec3 Scale = { 1.0f,1.0f,1.0f };
		std::string Name = "Transform Component";
		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3& translation)
			: Translation(translation) {}

		glm::mat4 GetTransform() const
		{
			glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));


			return glm::translate(glm::mat4(1.0f), Translation)
				* rotation
				* glm::scale(glm::mat4(1.0f), Scale);
		}
	};

	struct SpriteRendererComponent
	{
		glm::vec4 Color{1.0f};
		Ref<Texture2D> Texture;
		float TilingFactor = 1.0f;
		std::string Name = "Sprite Renderer Component";
		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const Ref<Texture2D> texture)
			: Texture(texture) {}
		SpriteRendererComponent(const glm::vec4& color)
			: Color(color) {}

	};

	struct CameraComponent
	{
		SceneCamera Camera;
		bool Primary = false;
		bool FixedAspectRatio = false;
		std::string Name = "Camera Component";
		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};

	class ScriptableEntity;

	struct NativeScriptComponent
	{
		ScriptableEntity* Instance = nullptr;

		ScriptableEntity* (*InstantiateScript)();
		void(*DestroyScript)(NativeScriptComponent*);

		template<typename T>
		void Bind()
		{
			InstantiateScript = []() {return static_cast<ScriptableEntity*>(new T()); };
		#if LWE_DEBUG
			DestroyScript = [](NativeScriptComponent* nsc) {delete nsc->Instance;  nsc->Instance = nullptr;  };
		#else
			DestroyScript = [](NativeScriptComponent* nsc) {delete  nsc->Instance; };
		#endif
		}

	};

	struct Rigidbody2DComponent
	{
		enum class BodyType { Static = 0, Dynamic, Kinematic};
		BodyType Type = BodyType::Static;
		bool FixedRotation = false;
		std::string Name = "Rigidbody2D Component";

		void* RuntimeBody = nullptr;

		Rigidbody2DComponent() = default;
		Rigidbody2DComponent(const Rigidbody2DComponent&) = default;
	};

	struct BoxCollider2DComponent
	{
		std::string Name = "BoxCollider2D Component";
		glm::vec2 Offset = { 0.0f,0.0f };
		glm::vec2 Size = { 0.5f,0.5f };

		float Density = 1.0f;
		float Friction = 0.5f;
		float Restitution = 0.0f;
		float RestitutionThreshold = 0.5f;

		void* RuntimeFixture = nullptr;

		BoxCollider2DComponent() = default;
		BoxCollider2DComponent(const BoxCollider2DComponent&) = default;
	};



	template<typename... Component>
	struct ComponentGroup
	{
	};

	using AllComponents =
		ComponentGroup < TransformComponent, SpriteRendererComponent,
		CameraComponent,
		Rigidbody2DComponent, BoxCollider2DComponent,
		NativeScriptComponent>;
}
