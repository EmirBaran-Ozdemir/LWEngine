#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui/imgui.h>
#include <better_enums/better_enums.h>

namespace LWEngine {

	BETTER_ENUM(ImGuiFontFamily, int,
		
		OpenSans = 0,
		PlusJakarta = 1,
		Roboto = 2
	);


	BETTER_ENUM(ImGuiFontWeight, int,
		
		Light = 0,
		Regular = 1,
		Bold = 2,
		Italic = 3
	);

	class ImGuiFont
	{
	public:
		~ImGuiFont() = default;
		virtual void Init() = 0;
		virtual bool IsValid() = 0;
		virtual void SetImGuiFont(ImGuiFontWeight fontWeight) = 0;
		virtual int GetFontFamilyIndex() = 0;
		virtual void Destroy() = 0;
	};

}