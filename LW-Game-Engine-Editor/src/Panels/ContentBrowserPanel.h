#pragma once
#include <glad/glad.h>

namespace LWEngine {
	
	class ContentBrowserPanel {

	public:
		ContentBrowserPanel();
		~ContentBrowserPanel();

		void OnImGuiRender();
	private:
		void DrawItems();
		bool InitTextures(const char* filename, GLuint* out_texture);
	private:
		std::string m_CurrentDir;

		GLuint m_FolderTexture = 0;
		char* m_FolderIconPath = "assets/icons/folder.png";
		GLuint m_FileTexture = 0;
		char* m_FileIconPath = "assets/icons/file.png";

	};
}
