#pragma once

#include "LWEngine/Core/UUID.h"
#include "LWEngine/Core/Timestep.h"
#include "LWEngine/Renderer/EditorCamera.h"

#include <entt.hpp>

class b2World;

namespace LWEngine {

	enum class SceneState {
		Play,
		Edit,
		Pause,
		Simulate
	};

	class Entity;
	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());
		Entity CreateEntityWithUUID(UUID uuid, const std::string& name = std::string());
		Entity CloneEntity(Entity entity);
		void DestroyEntity(Entity entity);

		void OnRuntimeStart();
		void OnRuntimeStop();
		void OnRuntimePause();

		void OnUpdateEditor(Timestep ts, EditorCamera& camera);
		void OnUpdateRuntime(Timestep ts);
		void OnResize(uint32_t width, uint32_t height);
		uint32_t GetWidth() const { return m_ViewportWidth; }
		uint32_t GetHeight() const { return m_ViewportHeight; }

		Entity GetPrimaryCameraEntity();
	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);
	private:
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

		b2World* m_BoxWorld = nullptr;

		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;
	};
}
