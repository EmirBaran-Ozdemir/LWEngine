#include "lwpch.h"
#include "FontMenu.h"
#include "Font/ImGuiFont.h"
#include "Font/ImGuiOpenSansFont.h"
#include "Font/ImGuiPlusJakartaFont.h"
#include "Font/ImGuiRobotoFont.h"

namespace LWEngine {

	FontMenu::FontMenu()
	{
		m_IO = ImGui::GetIO();
	}
	FontMenu::~FontMenu()
	{
	}

	bool FontMenu::AddFont(ImGuiFont* font)
	{
		int index = font->GetFontFamilyIndex();
		if (auto thm = m_Fonts.find(index); thm != m_Fonts.end())
			return false;

		if (!font->IsValid())
			return false;

		m_Fonts.emplace(index, font);
		ImGuiFontFamily family = ImGuiFontFamily::_from_integral(index);
		
		m_FontsFamily.emplace(index, family);
		m_FontsFamilyVector.push_back(std::make_pair(false, family));

		return true;
	}

	bool FontMenu::Init()
	{
		InitBuildInFonts();
		return true;
	}

	void FontMenu::AddWeights()
	{
		for (auto weight : ImGuiFontWeight::_values())
		{
			m_FontsWeightVector.push_back(std::make_pair(false, weight));
		}
	}
	void FontMenu::Render()
	{
		if (ImGui::BeginMenu("Font Families"))
		{
			for (int i = 0; i < m_FontsFamilyVector.size(); i++)
			{

				if (ImGui::MenuItem(m_FontsFamily.at(i)._to_string(), "", m_FontsFamilyVector[i].first, !m_FontsFamilyVector[i].first))
				{
					SelectFontFamily(m_FontsFamilyVector[i].second);
				}
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Font Families"))
		{
			ImGui::Separator();
			for (int i = 0; i < m_FontsWeightVector.size(); i++)
			{
				if (ImGui::MenuItem(m_FontsWeightVector.at(i).second._to_string(), "", m_FontsWeightVector[i].first, !m_FontsWeightVector[i].first))
				{
					SelectFontWeight(m_FontsWeightVector[i].second);
				}
			}
			ImGui::EndMenu();
		}
	}

	const char* FontMenu::GetMenuName()
	{
		return "Fonts";
	}

	void FontMenu::InitBuildInFonts()
	{
		AddWeights();
		ImGuiFont* font = new ImGuiOpenSansFont();
		font->Init();
		AddFont(font);
		SelectFontFamily(ImGuiFontFamily::OpenSans);
		SelectFontWeight(ImGuiFontWeight::Regular);

		font = new ImGuiPlusJakartaFont();
		font->Init();
		AddFont(font);
		font = new ImGuiRobotoFont();
		font->Init();
		AddFont(font);
	}

	void FontMenu::SelectFontFamily(ImGuiFontFamily fontFamily)
	{
		m_FontsFamilyVector[m_SelectedFontsFamilyIndex].first = false;
		m_SelectedFontsFamilyIndex = static_cast<int>(fontFamily);
		m_FontsFamilyVector[m_SelectedFontsFamilyIndex].first = true;
		SelectFont(fontFamily, m_FontsWeightVector[m_SelectedFontsWeightIndex].second);
	}

	void FontMenu::SelectFontWeight(ImGuiFontWeight fontWeight)
	{
		m_FontsWeightVector[m_SelectedFontsWeightIndex].first = false;
		m_SelectedFontsWeightIndex = static_cast<int>(fontWeight);
		m_FontsWeightVector[m_SelectedFontsWeightIndex].first = true;
		SelectFont(m_FontsFamilyVector[m_SelectedFontsFamilyIndex].second, fontWeight);
	}

	void FontMenu::SelectFont(ImGuiFontFamily fontFamily, ImGuiFontWeight fontWeight)
	{
		m_Fonts.at(fontFamily)->SetImGuiFont(fontWeight);
	}

	void FontMenu::Destroy()
	{
		for (const auto& pair : m_Fonts)
		{
			pair.second->Destroy();
		}
	}
}