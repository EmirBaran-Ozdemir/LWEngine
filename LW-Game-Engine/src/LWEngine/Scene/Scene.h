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
		void OnUpdate(Timestep ts);
		void OnResize(uint32_t width, uint32_t height);

	private:
		friend class Entity;
		entt::registry m_Registry;

		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
	};
}