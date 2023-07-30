#include "lwpch.h"
#include "Entity.h"

namespace LWEngine {

	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{
		
	}

}
