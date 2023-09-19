#pragma once

#include "LWEngine/Scene/Entity.h"

namespace LWEngine {

	class ScriptableEntity
	{
	public:
		virtual ~ScriptableEntity() {};
		template<typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}
		template<typename T>
		bool HasComponent()
		{
			return m_Entity.HasComponent<T>();
		}
		template<typename T>
		T& AddComponent()
		{
			return m_Entity.AddComponent<T>();
		}
	protected:
		virtual void OnCreate() {};
		virtual void OnUpdate(Timestep ts) {};
		virtual void OnDestroy() {};
	private:
		friend class Scene;
		Entity m_Entity;
	};
}