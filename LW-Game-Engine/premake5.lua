project "LW-Game-Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "lwpch.h"
	pchsource "src/lwpch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp",
		"vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp",
		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl",
	}
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"src",
		"vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.better_enums}",
		"%{IncludeDir.yaml_cpp}",
	}
	
	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"yaml-cpp",
		"opengl32.lib",
		"dwmapi.lib"
	}
	filter "system:windows"
		
		systemversion "latest"

		defines
		{
		}

	filter "configurations:Debug"
		defines "LWE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "LWE_RELEASE"
		runtime "Release"
		optimize "on"
	
	filter "configurations:Dist"
		defines "LWE_DIST"
		runtime "Release"
		optimize "on"