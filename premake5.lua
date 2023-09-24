include "./vendor/premake/premake_customization/solution_items.lua"

workspace "LW-Game-Engine"
	architecture "x86_64"
	startproject "LW-Game-Engine-Editor"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/LW-Game-Engine/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/LW-Game-Engine/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/LW-Game-Engine/vendor/imgui"
IncludeDir["glm"] = "%{wks.location}/LW-Game-Engine/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/LW-Game-Engine/vendor/stb_image"
IncludeDir["entt"] = "%{wks.location}/LW-Game-Engine/vendor/entt/include"
IncludeDir["better_enums"] = "%{wks.location}/LW-Game-Engine/vendor/better_enums"
IncludeDir["yaml_cpp"] = "%{wks.location}/LW-Game-Engine/vendor/yaml-cpp/include"

group "Dependencies"
	include "vendor/premake"
	include "LW-Game-Engine/vendor/GLFW"
	include "LW-Game-Engine/vendor/Glad"
	include "LW-Game-Engine/vendor/imgui"
	include "LW-Game-Engine/vendor/yaml-cpp"
group ""

include "LW-Game-Engine"
include "Sandbox"
include "ExampleGame"
include "LW-Game-Engine-Editor"
