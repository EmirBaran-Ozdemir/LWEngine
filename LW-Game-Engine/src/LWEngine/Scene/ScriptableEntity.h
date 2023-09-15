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
		
	protected:
		virtual void OnCreate() {};
		virtual void OnUpdate(Timestep ts) {};
		virtual void OnDestroy() {};
	private:
		friend class Scene;
		Entity m_Entity;
	};
}