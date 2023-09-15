#include "lwpch.h"
#include "Scene.h"

#include "LWEngine/Scene/Components.h"
#include "LWEngine/Renderer/Renderer2D.h"
#include <glm/glm.hpp>
#include "LWEngine/Scene/Entity.h"

namespace LWEngine {

	Scene::Scene()
	{
		entt::entity entity = m_Registry.create();
		m_Registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));

		TransformComponent& transformComponent = m_Registry.get<TransformComponent>(entity);

	}

	Scene::~Scene()
	{

	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create() ,this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;
		return entity;
	}


	void Scene::OnUpdate(Timestep ts)
	{
		//. Update scripts
		{
			LWE_PROFILE_SCOPE("Scene::OnUpdate - Scripts");
			m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
			{
				if (!nsc.Instance)
				{
					nsc.Instance = nsc.InstantiateScript();
					nsc.Instance->m_Entity = Entity{ entity,this };
					nsc.Instance->OnCreate();
				}
				nsc.Instance->OnUpdate(ts);
			});
		}

		//. Render 2D
		Camera* mainCamera = nullptr;
		glm::mat4* cameraTransform = nullptr;

		//? Rendering
		{
			//! Try to find main camera
			auto view = m_Registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view)
			{
				auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);
				if (camera.Primary)
				{
					mainCamera = &camera.Camera;
					cameraTransform = &transform.Transform;
					break;
				}
			}
		}

		if (mainCamera)
		{
			Renderer2D::BeginScene(mainCamera->GetProjection(), *cameraTransform);

			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
				Renderer2D::DrawQuad(transform, sprite.Color);
			}
			Renderer2D::EndScene();
		}
	}

	void Scene::OnResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		//! Resize 
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if (!cameraComponent.FixedAspectRatio)
				cameraComponent.Camera.SetViewportSize(width, height);

		}
	}
}