VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["stb_image"] = "%{wks.location}/LW-Game-Engine/vendor/stb_image"
IncludeDir["yaml_cpp"] = "%{wks.location}/LW-Game-Engine/vendor/yaml-cpp/include"
IncludeDir["GLFW"] = "%{wks.location}/LW-Game-Engine/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/LW-Game-Engine/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/LW-Game-Engine/vendor/ImGui"
IncludeDir["ImGuizmo"] = "%{wks.location}/LW-Game-Engine/vendor/ImGuizmo"
IncludeDir["glm"] = "%{wks.location}/LW-Game-Engine/vendor/glm"
IncludeDir["entt"] = "%{wks.location}/LW-Game-Engine/vendor/entt/include"
IncludeDir["shaderc"] = "%{wks.location}/LW-Game-Engine/vendor/shaderc/include"
IncludeDir["better_enums"] = "%{wks.location}/LW-Game-Engine/vendor/better_enums"
IncludeDir["SPIRV_Cross"] = "%{wks.location}/LW-Game-Engine/vendor/SPIRV-Cross"
IncludeDir["Box2D"] = "%{wks.location}/LW-Game-Engine/vendor/Box2D/include"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"

LibraryDir = {}

LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"
LibraryDir["VulkanSDK_Debug"] = "%{wks.location}/LW-Game-Engine/vendor/VulkanSDK/Lib"
LibraryDir["VulkanSDK_DebugDLL"] = "%{wks.location}/LW-Game-Engine/vendor/VulkanSDK/Bin"

Library = {}
Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
Library["VulkanUtils"] = "%{LibraryDir.VulkanSDK}/VkLayer_utils.lib"

Library["ShaderC_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/shaderc_sharedd.lib"
Library["SPIRV_Cross_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/spirv-cross-cored.lib"
Library["SPIRV_Cross_GLSL_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/spirv-cross-glsld.lib"
Library["SPIRV_Tools_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/SPIRV-Toolsd.lib"

Library["ShaderC_Release"] = "%{LibraryDir.VulkanSDK}/shaderc_shared.lib"
Library["SPIRV_Cross_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-core.lib"
Library["SPIRV_Cross_GLSL_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsl.lib"
