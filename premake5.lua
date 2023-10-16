include "./vendor/premake/premake_customization/solution_items.lua"
include "Dependencies.lua"

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


group "Dependencies"
	include "vendor/premake"
	include "LW-Game-Engine/vendor/GLFW"
	include "LW-Game-Engine/vendor/Box2D"
	include "LW-Game-Engine/vendor/Glad"
	include "LW-Game-Engine/vendor/imgui"
	include "LW-Game-Engine/vendor/yaml-cpp"
group ""

include "LW-Game-Engine"
include "Sandbox"
include "ExampleGame"
include "LW-Game-Engine-Editor"
