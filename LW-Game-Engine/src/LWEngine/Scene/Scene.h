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


	
		entt::registry m_Registry;
	};
}