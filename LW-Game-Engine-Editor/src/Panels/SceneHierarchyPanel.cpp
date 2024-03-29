#include "lwpch.h"

#include "Panels/SceneHierarchyPanel.h"
#include "LWEngine/Scene/Components.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui_internal.h>
#include "Font/ImGuiFont.h"
#include <cstring>

#ifdef _MSVC_LANG
#define _CRT_SECURE_NO_WARNINGS
#endif

namespace LWEngine {

	SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& context)
	{
		SetContext(context);
	}

	void SceneHierarchyPanel::SetContext(const Ref<Scene>& context)
	{
		m_Context = context;
		m_SelectedEntity = {};
	}

	void SceneHierarchyPanel::OnImGuiRender()
	{
		ImGui::Begin("Scene Hierarchy");

		m_Context->m_Registry.each([&](auto entityId)
			{
				Entity entity = { entityId, m_Context.get() };
				DrawEntityNode(entity);
			});

		if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && ImGui::IsWindowHovered())
			SetSelectedEntity(Entity());


		if (ImGui::BeginPopupContextWindow(nullptr, 1 | ImGuiPopupFlags_NoOpenOverItems))
		{
			if (ImGui::MenuItem("Create Entity"))
				m_Context->CreateEntity("New Entity");
			ImGui::EndPopup();
		}

		ImGui::End();

		ImGui::Begin("Properties");
		if (m_SelectedEntity)
		{
			DrawComponents(m_SelectedEntity);
		}
		ImGui::End();
	}

	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		auto const& tag = entity.GetComponent<TagComponent>().Tag;
		ImGuiTreeNodeFlags flags = (m_SelectedEntity == entity) * ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_Framed;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
		if (ImGui::IsItemClicked())
			m_SelectedEntity = entity;

		bool entityDeleted = false;
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete Entity"))
				entityDeleted = true;
			if (ImGui::MenuItem("Clone Entity"))
				m_Context->CloneEntity(entity);
			ImGui::EndPopup();
		}
		if (opened)
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
			if (bool opened = ImGui::TreeNodeEx((void*)384093, flags, tag.c_str()))
				ImGui::TreePop();
			ImGui::TreePop();
		}
		if (entityDeleted)
		{
			m_Context->DestroyEntity(entity);
			if (m_SelectedEntity == entity)
				m_SelectedEntity = {};
		}

	}

	static void DrawVec3Control(const std::string& label, glm::vec3& values, float& dragSpeed, float resetValue = 0.0f, const float columnWidth = 70.0f)
	{
		ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[ImGuiFontFamily::OpenSans + ImGuiFontWeight::Bold];

		ImGui::PushID(label.c_str());
		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();
		ImGui::PushMultiItemsWidths(4, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0.2f,0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight , lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0.15f, 255.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.9f, 0.2f, 0.2f, 255.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.8f, 0.2f, 0.2f, 255.0f));
		ImGui::PushFont(boldFont);
		if (ImGui::Button("X", buttonSize))
			values.x = resetValue;
		ImGui::PopFont();
		ImGui::SameLine();


		ImGui::DragFloat("##X", &values.x, dragSpeed, 0.0f, 0.0f, " %.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();
		ImGui::PopStyleColor(3);


		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.8f, 0.15f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.9f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.8f, 0.2f, 1.0f));
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Y", buttonSize))
			values.y = resetValue;
		ImGui::PopFont();
		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, dragSpeed, 0.0f, 0.0f, " %.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();
		ImGui::PopStyleColor(3);


		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.15f, 0.1f, 0.8f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.2f, 0.9f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.2f, 0.8f, 1.0f));
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Z", buttonSize))
			values.z = resetValue;
		ImGui::PopFont();
		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, dragSpeed, 0.0f, 0.0f, " %.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();
		ImGui::PopStyleColor(3);
		ImGui::PopStyleVar();

		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 2.0f);
		ImGui::DragFloat("##Speed", &dragSpeed, 0.01f, 0.01f, 1.0f, "%.2f");

		ImGui::Columns(1);
		ImGui::PopID();
	}



	void SceneHierarchyPanel::DrawComponents(Entity entity)
	{
		if (entity.HasComponent<TagComponent>())
		{
			auto& tag = entity.GetComponent<TagComponent>().Tag;
			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			std::strncpy(buffer, tag.c_str(), sizeof(buffer));

			if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
			{
				tag = std::string(buffer);
			}
		}

		ImGui::SameLine();
		ImGui::PushItemWidth(-1);
		if (ImGui::Button("Add Component"))
			ImGui::OpenPopup("AddComponent");

		static std::string component = "";
		if (ImGui::BeginPopup("AddComponent"))
		{
			if (!m_SelectedEntity.HasComponent<CameraComponent>())
			{
				if (ImGui::MenuItem("Camera"))
				{
					component = ComponentAddCheck<CameraComponent>();
					ImGui::CloseCurrentPopup();
				}
			}
			if (!m_SelectedEntity.HasComponent<SpriteRendererComponent>())
			{
				if (ImGui::MenuItem("Sprite Renderer"))
				{
					component = ComponentAddCheck<SpriteRendererComponent>();
					ImGui::CloseCurrentPopup();
				}
			}
			if (!m_SelectedEntity.HasComponent<TransformComponent>())
			{
				if (ImGui::MenuItem("Transform"))
				{
					component = ComponentAddCheck<TransformComponent>();
					ImGui::CloseCurrentPopup();
				}
			}
			if (!m_SelectedEntity.HasComponent<Rigidbody2DComponent>())
			{
				if (ImGui::MenuItem("Rigidbody"))
				{
					component = ComponentAddCheck<Rigidbody2DComponent>();
					ImGui::CloseCurrentPopup();
				}
			}
			if (!m_SelectedEntity.HasComponent<BoxCollider2DComponent>())
			{
				if (ImGui::MenuItem("BoxCollider"))
				{
					component = ComponentAddCheck<BoxCollider2DComponent>();
					ImGui::CloseCurrentPopup();
				}
			}

			ImGui::EndPopup();
		}
		ImGui::PopItemWidth();

		DrawComponent<TransformComponent>("Transform", entity, [](auto& component)
			{
				static float positionDragSpeed = 0.01f;
				static float rotationDragSpeed = 1.0f;
				static float scaleDragSpeed = 0.03f;
				DrawVec3Control("Position", component.Translation, positionDragSpeed);
				glm::vec3 rotation = glm::degrees(component.Rotation);
				DrawVec3Control("Rotation", rotation, rotationDragSpeed);
				component.Rotation = glm::radians(rotation);
				DrawVec3Control("Scale", component.Scale, scaleDragSpeed);
			});

		DrawComponent<SpriteRendererComponent>("Sprite Renderer", entity, [this](auto& component)
			{
				FileSystem fSystem;
				ImGui::Columns(2);
				ImGui::SetColumnWidth(0, 100);
				ImGui::SetColumnWidth(1, 300);
				ImGui::Text("Color");
				ImGui::NextColumn();
				ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
				ImGui::ColorEdit4("##Color", glm::value_ptr(component.Color));

				ImGui::NextColumn();
				ImGui::Text("Tiling Factor");
				ImGui::NextColumn();
				ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
				ImGui::DragFloat("##Tiling Factor", &component.TilingFactor, 0.1f, 0.0f, 10.0f);

				ImGui::NextColumn();
				ImGui::Text("Texture");
				ImGui::NextColumn();
				ImGui::SetNextItemWidth(300);
				std::string texturePath = "No Texture";
				if (component.Texture)
				{
					texturePath = component.Texture->GetPath();
					texturePath = fSystem.GetFileNameWithExtension(texturePath);
				}
				ImGui::Button(texturePath.c_str(), ImVec2(200.0f, 0.0f));
				if (ImGui::BeginPopupContextItem())
				{
					if (ImGui::MenuItem("Delete Texture"))
						component.Texture.reset();
					ImGui::EndPopup();
				}

				if (ImGui::BeginDragDropTarget())
				{
					if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
					{
						const char* path = (const char*)payload->Data;
						FileType type = fSystem.GetFileType(path);
						if (type == FileType::png || type == FileType::jpg)
						{
							component.Texture = Texture2D::Create(path);
						}
					}
					ImGui::EndDragDropTarget();
				}
				ImGui::Columns(1);

			});

		DrawComponent<Rigidbody2DComponent>("Rigidbody", entity, [](auto& component)
			{
				const char* bodyTypeStrings[] = { "Static", "Dynamic", "Kinematic" };
				int typeCount = sizeof(bodyTypeStrings) / sizeof(bodyTypeStrings[0]);
				auto bodyTypeId = (int)component.Type;

				if (const char* currentBodyTypeString = bodyTypeStrings[bodyTypeId]; ImGui::BeginCombo("Body Type", currentBodyTypeString))
				{
					for (int i = 0; i < typeCount; i++)
					{
						bool isSelected = i == bodyTypeId;

						if (ImGui::Selectable(bodyTypeStrings[i], isSelected))
						{
							currentBodyTypeString = bodyTypeStrings[i];
							component.Type = (Rigidbody2DComponent::BodyType)i;
						}
						if (isSelected)
							ImGui::SetItemDefaultFocus();
					}
					ImGui::EndCombo();
				}
				ImGui::Checkbox("Fixed Rotation", &component.FixedRotation);
			});

		DrawComponent<BoxCollider2DComponent>("Box Collider", entity, [](auto& component)
			{
				ImGui::DragFloat2("Offset", glm::value_ptr(component.Offset));
				ImGui::DragFloat2("Size", glm::value_ptr(component.Size));
				ImGui::DragFloat("Density", &component.Density, 0.01f, 0.01f, 1.0f);
				ImGui::DragFloat("Friction", &component.Friction, 0.01f, 0.01f, 1.0f);
				ImGui::DragFloat("Restitution", &component.Restitution, 0.01f, 0.01f, 1.0f);
				ImGui::DragFloat("Restitution", &component.RestitutionThreshold, 0.01f, 0.01f);
			});

		DrawComponent<CameraComponent>("Camera", entity, [](auto& component)
			{
				auto& camera = component.Camera;

				ImGui::Checkbox("Primary", &component.Primary);

				const char* projectionTypeStrings[] = { "Perspective", "Orthographic" };

				auto projectionTypeId = (int)camera.GetProjectionType();

				if (const char* currentProjectionTypeString = projectionTypeStrings[projectionTypeId]; ImGui::BeginCombo("Projection", currentProjectionTypeString))
				{
					for (int i = 0; i < 2; i++)
					{
						bool isSelected = i == projectionTypeId;

						if (ImGui::Selectable(projectionTypeStrings[i], isSelected))
						{
							currentProjectionTypeString = projectionTypeStrings[i];
							camera.SetProjectionType(i);
						}
						if (isSelected)
							ImGui::SetItemDefaultFocus();
					}
					ImGui::EndCombo();
				}

				if (camera.GetProjectionType() == SceneCamera::ProjectionType::Perspective)
				{
					if (float perspectiveFOV = glm::degrees(camera.GetPerspectiveVerticalFOV()); ImGui::DragFloat("FOV", &perspectiveFOV))
						camera.SetPerspectiveVerticalFOV(glm::radians(perspectiveFOV));

					if (float perspectiveNear = camera.GetPerspectiveNearClip(); ImGui::DragFloat("Near", &perspectiveNear))
						camera.SetPerspectiveNearClip(perspectiveNear);

					
					if (float perspectiveFar = camera.GetPerspectiveFarClip(); ImGui::DragFloat("Far", &perspectiveFar))
						camera.SetPerspectiveFarClip(perspectiveFar);
				}

				if (camera.GetProjectionType() == SceneCamera::ProjectionType::Orthographic)
				{
					if (float orthoSize = camera.GetOrthographicSize(); ImGui::DragFloat("Size", &orthoSize))
						camera.SetOrthographicSize(orthoSize);

					if (float orthoNear = camera.GetOrthographicNearClip(); ImGui::DragFloat("Near", &orthoNear))
						camera.SetOrthographicNearClip(orthoNear);

					if (float orthoFar = camera.GetOrthographicFarClip(); ImGui::DragFloat("Far", &orthoFar))
						camera.SetOrthographicFarClip(orthoFar);

					ImGui::Checkbox("Fixed aspect ratio", &component.FixedAspectRatio);
				}
			});
	}

	template <typename T>
	std::string SceneHierarchyPanel::ComponentAddCheck()
	{
		T component;
		if (!m_SelectedEntity.HasComponent<T>())
		{
			m_SelectedEntity.AddComponent<T>();
			static const std::string empty = "";
			return empty;
		}
		else
		{
			LWE_CORE_WARN("Warning: This entity already has the {0}!", component.Name);
			return component.Name;
		}
	}
}
