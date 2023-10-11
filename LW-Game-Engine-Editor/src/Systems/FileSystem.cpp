#include "lwpch.h"
#include "Systems/FileSystem.h"

namespace LWEngine {

	FileSystem::FileSystem()
	{
		m_ExtensionMap = {
			{ "txt",	txt },
			{ "hlsl",	hlsl },
			{ "glsl",	glsl },
			{ "c",		c_src },
			{ "h",		c_header },
			{ "cpp",	cpp_src },
			{ "json",	json },
			{ "spv",	spirv },
			{ "obj",	obj },
			{ "lwe",	lwe},
			{ "png",	png},
			{ "jpg",	jpg}
		};

	}

	FileType FileSystem::GetFileType(const char* str)
	{
		std::string fileExtension = GetExtension(str);
		auto it = m_ExtensionMap.find(fileExtension);

		if (it != m_ExtensionMap.end()) {
			return it->second;
		}
		else {
			return FileType::unknown;
		}
	}

	std::string FileSystem::GetExtension(const char* str)
	{
		const char* dot = strrchr(str, '.');
		if (!dot || dot == str) {
			return "";
		}
		return dot + 1;
	}

	std::string FileSystem::GetFileNameWithExtension(const std::string& path) {
		size_t found = path.find_last_of("/\\");
		if (found != std::string::npos) {
			return path.substr(found + 1);
		}
		return path;
	}
}
