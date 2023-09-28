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
		Entity GetSelectedEntity() const { return m_SelectedEntity; }
		void SetSelectedEntity(Entity entity) { m_SelectedEntity = entity; }
	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
		template <typename T>
		const std::string ComponentAddCheck();
	private:
		Ref<Scene> m_Context;
		Entity m_SelectedEntity;
	};
}
