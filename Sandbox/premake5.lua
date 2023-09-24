project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}
	
	includedirs
	{
		"%{wks.location}/LW-Game-Engine/vendor/spdlog/include",
		"%{wks.location}/LW-Game-Engine/vendor",
		"%{wks.location}/LW-Game-Engine/src",
		"%{IncludeDir.glm}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.entt}",
	}

	links
	{
		"LW-Game-Engine"
	}

	filter "system:windows"
		systemversion "latest"

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