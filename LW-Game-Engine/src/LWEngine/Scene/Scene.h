#pragma once

#include <entt.hpp>
#include "LWEngine/Core/Timestep.h"

namespace LWEngine {

	class Entity;
	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());
		Entity CloneEntity(Entity entity);
		void DestroyEntity(Entity entity);

		void OnUpdate(Timestep ts);
		void OnResize(uint32_t width, uint32_t height);
		uint32_t GetWidth() const { return m_ViewportWidth; }
		uint32_t GetHeight() const { return m_ViewportHeight; }
	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);
	private:
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
		friend class Entity;
		friend class SceneHierarchyPanel;
	};
}