#include "lwpch.h"
#include "Panels/ContentBrowserPanel.h"

#include <filesystem>
#include <imgui/imgui.h>
#include <stb_image/stb_image.h>

namespace LWEngine {

	ContentBrowserPanel::ContentBrowserPanel()
	{
		//? Get current path
		std::string executablePath = std::filesystem::current_path().string();
		m_CurrentDir = executablePath + "\\assets";

		//? Folder - File Textures
		bool folderRes = InitTextures(m_FolderIconPath, &m_FolderTexture);
		LWE_ASSERT(folderRes, "ERROR::TEXTURE_INIT::{0}", m_FolderIconPath);

		bool fileRes = InitTextures(m_FileIconPath, &m_FileTexture);
		LWE_ASSERT(fileRes, "ERROR::TEXTURE_INIT::{0}", m_FileIconPath);
	}

	ContentBrowserPanel::~ContentBrowserPanel()
	{

	}
	void ContentBrowserPanel::OnImGuiRender()
	{
		bool enteredFolder = false;
		std::string entry;
		ImGui::Begin("Content Browser");

		if (ImGui::Button(" < "))
		{
			size_t lastSlashPos = m_CurrentDir.find_last_of('\\');
			if (lastSlashPos != std::string::npos)
			{
				m_CurrentDir.erase(lastSlashPos);
			}
		}
		ImGui::SameLine();
		ImGui::Text("%s", m_CurrentDir.c_str());
		ImGui::Separator();
		//ADD SPACING
		static float padding = 64.f;
		static float btnSize = 50.f;
		static int frame = btnSize / 2;
		float cellSize = padding + btnSize;
		int columnCount = static_cast<int>(ImGui::GetContentRegionAvail().x / cellSize);
		if (columnCount < 1)
			columnCount = 1;
		ImGui::Columns(columnCount, 0, false);

		for (auto& file : std::filesystem::directory_iterator(m_CurrentDir))
		{
			std::string path = file.path().filename().string();
			bool isDirectory = std::filesystem::is_directory(file);
			int iconTexture = isDirectory ? m_FolderTexture : m_FileTexture;
			ImGui::PushID(path.c_str());
			float centerBegin = ImGui::GetCursorPosX() + (btnSize) * 0.5f;
			ImGui::SetCursorPosX(centerBegin);
			if (ImGui::ImageButton((void*)(intptr_t)iconTexture, ImVec2(50, 50), { 0, 1 }, { 1, 0 }))
			{
				if (!enteredFolder && isDirectory)
				{
					enteredFolder = true;
					entry = path;
				}

				std::cout << "clicked";
			}
			ImGui::PopID();
			float textWidth = ImGui::CalcTextSize(path.c_str()).x;
			auto textBegin = ImGui::GetCursorPosX() + ((btnSize + frame * 2 - textWidth) * 0.5f);
			if (textBegin >= ImGui::GetCursorPosX())
				ImGui::SetCursorPosX(textBegin);

			ImGui::Text("%s", path.c_str());
			ImGui::NextColumn();
		}
		if (enteredFolder)
		{
			auto path = entry;
			std::string suffix = "\\" + path;
			m_CurrentDir.append(suffix.c_str());

		}

		ImGui::End(); // Content Browser
	}


	void ContentBrowserPanel::DrawItems()
	{

	}

	bool ContentBrowserPanel::InitTextures(const char* filename, GLuint* out_texture)
	{
		int image_width = 0;
		int image_height = 0;

		unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
		if (image_data == NULL)
			return false;

		GLuint image_texture;
		glGenTextures(1, &image_texture);

		glBindTexture(GL_TEXTURE_2D, image_texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
		stbi_image_free(image_data);

		*out_texture = image_texture;
		return true;
	}


}
