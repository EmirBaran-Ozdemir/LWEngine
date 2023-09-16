#pragma once

#include "Scene.h"
#include <entt.hpp>

namespace LWEngine {

	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;


		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			LWE_CORE_ASSERT(!HasComponent<T>(), "ERROR::ENTITY::ALREADY_HAS_COMPONENTS");

			return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			LWE_CORE_ASSERT(HasComponent<T>(), "ERROR::ENTITY::DOES_NOT_HAVE_COMPONENTS");
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		//template<typename T>
		//std::vector<Component>& GetAllComponents()
		//{
		//	LWE_CORE_ASSERT(HasComponent<T>(), "ERROR::ENTITY::DOES_NOT_HAVE_COMPONENTS");
		//	return m_Scene->m_Registry.all_of<T>(m_EntityHandle);
		//}

		template<typename T>
		void RemoveComponent()
		{
			LWE_CORE_ASSERT(HasComponent<T>(), "ERROR::ENTITY::DOES_NOT_HAVE_COMPONENTS");
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.any_of<T>(m_EntityHandle);
		}

		operator bool() const { return m_EntityHandle != entt::null; }
		operator uint32_t() const { return (uint32_t)m_EntityHandle; }
		bool operator==(const Entity& other) const { return m_EntityHandle == other.m_EntityHandle && m_Scene == other.m_Scene; }
		bool operator!=(const Entity& other) const { return !operator==(other); }
	private:
		entt::entity m_EntityHandle{ entt::null };
		Scene* m_Scene = nullptr;
	};
}