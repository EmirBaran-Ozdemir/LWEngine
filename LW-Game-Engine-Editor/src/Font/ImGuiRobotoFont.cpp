#include "lwpch.h"
#include "ImGuiRobotoFont.h"

namespace LWEngine {

	ImGuiRobotoFont::ImGuiRobotoFont()
	{
		m_FamilyIndex = ImGuiFontFamily::Roboto;
	}
	void ImGuiRobotoFont::Init()
	{
		ImGuiIO& io = ImGui::GetIO();
		io.Fonts->AddFontFromFileTTF("resources/fonts/roboto/Roboto-Light.ttf", 17);
		io.Fonts->AddFontFromFileTTF("resources/fonts/roboto/Roboto-Regular.ttf", 17);
		io.Fonts->AddFontFromFileTTF("resources/fonts/roboto/Roboto-Bold.ttf", 17);
		io.Fonts->AddFontFromFileTTF("resources/fonts/roboto/Roboto-Italic.ttf", 17);
	}
	bool ImGuiRobotoFont::IsValid()
	{
		return true;
	}

	void ImGuiRobotoFont::Destroy()
	{
		//TODO: Add Destroy
	}
	void ImGuiRobotoFont::SetImGuiFont(ImGuiFontWeight fontWeight)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.FontDefault = io.Fonts->Fonts[(m_FamilyIndex * 4) + fontWeight];
	}
	int ImGuiRobotoFont::GetFontFamilyIndex()
	{
		return m_FamilyIndex;
	}
}
