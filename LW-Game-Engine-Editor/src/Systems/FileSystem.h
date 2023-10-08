#pragma once

#include <unordered_map>
#include <string>

namespace LWEngine {

	enum FileType {
		unknown,
		folder,
		txt,
		hlsl,
		glsl,
		c_src,
		c_header,
		cpp_src,
		json,
		spirv,
		obj,
		lwe,
		png,
		jpg
	};

	class FileSystem {
	public:
		FileSystem();

		FileType GetFileType(const char* str);

	private:
		std::unordered_map<std::string, FileType> extension_map;

		std::string GetExtension(const char* str);
	};

}
