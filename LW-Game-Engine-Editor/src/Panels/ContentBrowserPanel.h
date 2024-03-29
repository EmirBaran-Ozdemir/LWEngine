#pragma once
#include <glad/glad.h>
#include "Systems/FileSystem.h"
#include "LWEngine/Renderer/Renderer2D.h"

namespace LWEngine {

	class ContentBrowserPanel {

	public:
		ContentBrowserPanel();

		void OnImGuiRender();
	private:
		std::string m_CurrentDir;

		Ref<Texture2D> m_FolderIcon = 0;
		char* m_FolderIconPath = "resources/icons/folder.png";
		Ref<Texture2D> m_FileIcon = 0;
		char* m_FileIconPath = "resources/icons/file.png";

		bool m_TextOnly = false;
	};
}
