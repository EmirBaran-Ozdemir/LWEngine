#pragma once

#include <LWEngine/Scene/Entity.h>
#include "LWEngine/Scene/Scene.h"
#include <Systems/FileSystem.h>

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
		std::string ComponentAddCheck();
	private:
		Ref<Scene> m_Context;
		Entity m_SelectedEntity;
	};

	template<typename T, typename UIFunction>
	static void DrawComponent(const std::string& label, Entity entity, UIFunction uiFunction)
	{
		const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_FramePadding;

		if (entity.HasComponent<T>())
		{
			ImVec2 ContentRegionAvailable = ImGui::GetContentRegionAvail();
			auto& component = entity.GetComponent<T>();
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4,4 });
			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImGui::Separator();
			bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, "%s", label.c_str());
			ImGui::PopStyleVar();
			ImGui::SameLine(ContentRegionAvailable.x - lineHeight * 0.5f);
			if (ImGui::Button("+", ImVec2{ lineHeight,lineHeight }))
			{
				ImGui::OpenPopup("Component Settings");
			}
			bool removed = false;
			if (ImGui::BeginPopup("Component Settings"))
			{
				std::string menuString = "Delete" + label + "Component";
				if (ImGui::MenuItem(menuString.c_str()))
					removed = true;
				ImGui::EndPopup();
			}
			if (open)
			{
				uiFunction(component);
				ImGui::TreePop();
			}
			if (removed)
				entity.RemoveComponent<T>();
		}
	}


}
