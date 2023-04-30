workspace "LW-Game-Engine"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.ststem}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "LW-Game-Engine/vendor/GLFW/include"
IncludeDir["Glad"] = "LW-Game-Engine/vendor/Glad/include"
IncludeDir["ImGui"] = "LW-Game-Engine/vendor/imgui"


include "LW-Game-Engine/vendor/GLFW"
include "LW-Game-Engine/vendor/Glad"
include "LW-Game-Engine/vendor/imgui"


project "LW-Game-Engine"
	location "LW-Game-Engine"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "lwpch.h"
	pchsource "LW-Game-Engine/src/lwpch.h"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}
	
	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib",
		"dwmapi.lib"
	}
	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"LWE_PLATFORM_WINDOWS",
			"LWE_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}


	filter "configurations:Debug"
		defines "LWE_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "LWE_RELEASE"
		runtime "Release"
		optimize "On"
	
	filter "configurations:Dist"
		defines "LWE_DIST"
		runtime "Release"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	staticruntime "off"

	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"LW-Game-Engine/vendor/spdlog/include",
		"LW-Game-Engine/src"
	}
	links
	{
		"LW-Game-Engine"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"LWE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "LWE_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "LWE_RELEASE"
		runtime "Release"
		optimize "On"
	
	filter "configurations:Dist"
		defines "LWE_DIST"
		runtime "Release"
		optimize "On"