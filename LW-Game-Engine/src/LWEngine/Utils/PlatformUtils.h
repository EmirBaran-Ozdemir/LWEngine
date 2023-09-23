#pragma once

#include <string>
#include <commdlg.h>

namespace LWEngine {

	class FileDialogs
	{
	public:
		static std::string OpenFile(const char* filter);
		static std::string SaveFile(const char* filter);
	};
}