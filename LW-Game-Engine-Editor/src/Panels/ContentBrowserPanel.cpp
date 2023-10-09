#include "lwpch.h"
#include "Panels/ContentBrowserPanel.h"

#include <filesystem>
#include <imgui/imgui.h>
#include <stb_image/stb_image.h>
#include <imgui/imgui_internal.h>


namespace LWEngine {

	ContentBrowserPanel::ContentBrowserPanel()
	{
		//? Get current path
		std::string executablePath = std::filesystem::current_path().string();
		m_CurrentDir = executablePath + "/assets";

		//? Folder - File Textures
		m_FolderIcon = Texture2D::Create(m_FolderIconPath);
		m_FileIcon = Texture2D::Create(m_FileIconPath);
	}

	void ContentBrowserPanel::OnImGuiRender()
	{
		static float padding = 64.f;
		static float btnSize = 50.f;
		static int frame = btnSize / 2;
		float cellSize = padding + btnSize;
		int columnCount = static_cast<int>(ImGui::GetContentRegionAvail().x / cellSize);
		if (columnCount < 1)
			columnCount = 1;
		std::string entry;
		ImGui::Begin("Content Browser");
		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		if (ImGui::Button(" < "))
		{
			size_t lastSlashPos = m_CurrentDir.find_last_of('/');
			if (lastSlashPos != std::string::npos)
			{
				m_CurrentDir.erase(lastSlashPos);
			}
		}
		ImGui::PopItemWidth();
		ImGui::SameLine();
		ImGui::Text("%s", m_CurrentDir.c_str());
		ImGui::PopItemWidth();
		float paddingSilderWdt = ImGui::GetContentRegionAvail().x * 0.2f;
		float paddingTxWdt = ImGui::CalcTextSize("Padding").x;
		float onlyNamesTxWdt = ImGui::CalcTextSize("File names only").x;
		float onlyNamesChBxSz = 40.0f;
		ImGui::SameLine(ImGui::GetContentRegionAvail().x - onlyNamesTxWdt - onlyNamesChBxSz - paddingSilderWdt - paddingTxWdt - ImGui::GetStyle().ItemSpacing.x * 3);
		ImGui::Text("File names only");
		ImGui::SameLine(ImGui::GetContentRegionAvail().x - onlyNamesChBxSz - paddingSilderWdt - paddingTxWdt - ImGui::GetStyle().ItemSpacing.x * 2);
		ImGui::Checkbox("##File names only", &m_TextOnly);
		ImGui::SameLine(ImGui::GetContentRegionAvail().x - paddingSilderWdt - paddingTxWdt - ImGui::GetStyle().ItemSpacing.x);
		ImGui::Text("Padding");
		ImGui::SameLine(ImGui::GetContentRegionAvail().x - paddingSilderWdt);
		ImGui::SetNextItemWidth(paddingSilderWdt);
		ImGui::SliderFloat("##Padding", &padding, 32, 256, "%.3f");
		ImGui::PopItemWidth();
		ImGui::Columns(columnCount, 0, false);

		bool enteredFolder = false;
		bool openedFile = false;
		FileType type = unknown;
		for (auto& file : std::filesystem::directory_iterator(m_CurrentDir))
		{
			auto relativePath = std::filesystem::relative(file.path());
			std::string path = file.path().filename().string();

			bool isDirectory = std::filesystem::is_directory(file);
			ImGui::PushID(path.c_str());
			float centerBegin = ImGui::GetCursorPosX() + (btnSize) * 0.5f;
			ImGui::SetCursorPosX(centerBegin);
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
			if (!m_TextOnly)
			{
				Ref<Texture2D> icon = isDirectory ? m_FolderIcon : m_FileIcon;
				ImGui::ImageButton((ImTextureID)icon->GetRendererID(), ImVec2(50, 50), { 0, 1 }, { 1, 0 });
			}
			else
			{
				std::string type = isDirectory ? "DIR\n" : "FILE\n";
				type = type + path;
				ImGui::Button(type.c_str());
			}

			ImGui::PopStyleColor();

			if (ImGui::BeginDragDropSource())
			{
				std::string tempString = relativePath.string();
				const char* itemPath = tempString.c_str();
				ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", itemPath, strlen(itemPath) + 1);
				ImGui::TextUnformatted(itemPath);
				ImGui::EndDragDropSource();
			}

			if (ImGui::IsItemHovered())
			{
				if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
				{
					if (!enteredFolder && isDirectory)
					{
						enteredFolder = true;
						entry = path;
					}
				}
			}
			if (!m_TextOnly)
			{
				float textWidth = ImGui::CalcTextSize(path.c_str()).x;
				auto textBegin = ImGui::GetCursorPosX() + ((btnSize + frame * 2 - textWidth) * 0.5f);
				if (textBegin >= ImGui::GetCursorPosX())
					ImGui::SetCursorPosX(textBegin);
				ImGui::Text("%s", path.c_str());
			}
			ImGui::NextColumn();
			ImGui::PopID();
		}
		if (enteredFolder)
		{
			auto path = entry;
			std::string suffix = "/" + path;
			m_CurrentDir.append(suffix.c_str());
		}


		ImGui::End(); // Content Browser
	}
}
