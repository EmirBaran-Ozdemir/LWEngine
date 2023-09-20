#pragma once
#include "IImGuiTheme.h"
#include <string>

namespace LWEngine {

	class ImGuiDarkBlueTheme : public IImGuiTheme
	{
	public:
		ImGuiDarkBlueTheme();
		virtual bool IsValid() override;
		virtual const char* GetThemeName() override;
		virtual void SetImGuiTheme(ImGuiStyle& style) override;
		virtual bool Init() override;
		virtual void Destroy() override;
	private:
		std::string m_Name;

	};
}