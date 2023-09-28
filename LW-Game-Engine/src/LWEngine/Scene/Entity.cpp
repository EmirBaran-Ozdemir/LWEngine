#include "lwpch.h"
#include "Entity.h"

namespace LWEngine {

	Entity::Entity(int handle, Scene* scene)
		: m_EntityHandle(entt::entity(handle)), m_Scene(scene)
	{

	}
	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{
		
	}

}
