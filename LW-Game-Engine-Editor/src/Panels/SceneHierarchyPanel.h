#pragma once
#include <LWEngine/Scene/Entity.h>
#include "LWEngine/Scene/Scene.h"

namespace LWEngine {

	class SceneHierarchyPanel 
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& context);
		void OnImGuiRender();
		void SetContext(const Ref<Scene>& context);
	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};
}