#include "lwpch.h"
#include "ImGuiPlusJakartaFont.h"

namespace LWEngine {

	ImGuiPlusJakartaFont::ImGuiPlusJakartaFont()
	{
		m_FamilyIndex = ImGuiFontFamily::PlusJakarta;
	}
	void ImGuiPlusJakartaFont::Init()
	{
		ImGuiIO& io = ImGui::GetIO();
		io.Fonts->AddFontFromFileTTF("resources/fonts/plusjakarta/PlusJakartaSans-Light.ttf", 17);
		io.Fonts->AddFontFromFileTTF("resources/fonts/plusjakarta/PlusJakartaSans-Regular.ttf", 17);
		io.Fonts->AddFontFromFileTTF("resources/fonts/plusjakarta/PlusJakartaSans-Bold.ttf", 17);
		io.Fonts->AddFontFromFileTTF("resources/fonts/plusjakarta/PlusJakartaSans-Italic.ttf", 17);
	}
	bool ImGuiPlusJakartaFont::IsValid()
	{
		return true;
	}

	void ImGuiPlusJakartaFont::Destroy()
	{
		//TODO: Add Destroy
	}
	void ImGuiPlusJakartaFont::SetImGuiFont(ImGuiFontWeight fontWeight)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.FontDefault = io.Fonts->Fonts[(m_FamilyIndex * 4) + fontWeight];
	}
	int ImGuiPlusJakartaFont::GetFontFamilyIndex()
	{
		return m_FamilyIndex;
	}
}
