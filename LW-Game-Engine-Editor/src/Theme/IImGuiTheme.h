#pragma once
#include <string>

class ImGuiStyle;
namespace LWEngine {


	class IImGuiTheme
	{
	public:
		virtual ~IImGuiTheme() = default;
		virtual bool IsValid() = 0;
		virtual const char* GetThemeName() = 0;
		virtual void SetImGuiTheme(ImGuiStyle& style) = 0;

		virtual bool Init() = 0;
		virtual void Destroy() = 0;
	};
}
