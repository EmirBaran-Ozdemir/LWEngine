#include "lwpch.h"
#include "ImGuiOpenSansFont.h"

namespace LWEngine {

	ImGuiOpenSansFont::ImGuiOpenSansFont()
	{
		m_FamilyIndex = ImGuiFontFamily::OpenSans;
	}
	void ImGuiOpenSansFont::Init()
	{
		ImGuiIO& io = ImGui::GetIO();
		io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Light.ttf", 18);
		io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Regular.ttf", 18);
		io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Bold.ttf", 18);
		io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Italic.ttf", 18);
	}
	bool ImGuiOpenSansFont::IsValid()
	{
		return true;
	}

	void ImGuiOpenSansFont::Destroy() 
	{
		//TODO: Add Destroy
	}
	void ImGuiOpenSansFont::SetImGuiFont(ImGuiFontWeight fontWeight)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.FontDefault = io.Fonts->Fonts[(m_FamilyIndex * 4) + fontWeight];
	}
	int ImGuiOpenSansFont::GetFontFamilyIndex()
	{
		return m_FamilyIndex;
	}
}
