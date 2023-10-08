#include "lwpch.h"
#include "Systems/FileSystem.h"

namespace LWEngine {

	FileSystem::FileSystem()
	{
		extension_map = {
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
		std::string file_extension = GetExtension(str);
		auto it = extension_map.find(file_extension);

		if (it != extension_map.end()) {
			return it->second;
		}
		else {
			return unknown;
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
}
