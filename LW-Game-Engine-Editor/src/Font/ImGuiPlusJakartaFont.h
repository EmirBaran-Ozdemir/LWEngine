#pragma once
#include "ImGuiFont.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui/imgui.h>

namespace LWEngine {

	class ImGuiPlusJakartaFont : public ImGuiFont
	{
	public:
		ImGuiPlusJakartaFont();
		virtual void Init() override;
		virtual bool IsValid() override;
		virtual void Destroy() override;
		virtual void SetImGuiFont(ImGuiFontWeight fontWeight) override;
		virtual int GetFontFamilyIndex() override;
	private:
		int m_FamilyIndex;
	};
}
