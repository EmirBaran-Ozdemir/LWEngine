#pragma once

#include "LWEngine.h"
#include "Panels/SceneHierarchyPanel.h"
#include "Panels/WindowPanel.h"
#include "Panels/ContentBrowserPanel.h"

#include "Extras/ParticleSystem.h"
#include "Extras/WorldGeneration.h"
#include "Extras/Player.h"
#include <Systems/FileSystem.h>

namespace LWEngine {
	struct vec4Hash
	{
		std::size_t operator()(const glm::vec4& vec) const
		{
			std::size_t h1 = std::hash<float>{}(vec.x);
			std::size_t h2 = std::hash<float>{}(vec.y);
			std::size_t h3 = std::hash<float>{}(vec.z);
			std::size_t h4 = std::hash<float>{}(vec.w);

			return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3);
		}
	};

	struct vec4Equal
	{
		bool operator()(const glm::vec4& lhs, const glm::vec4& rhs) const
		{
			return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
		}
	};


	class EditorLayer : public Layer
	{
	public:
		explicit EditorLayer(std::string& path);
		~EditorLayer() final = default;

		void OnAttach() override;
		void OnDetach() override;


		void OnUpdate(Timestep ts) override;
		void OnImGuiRender(Timestep ts) override;
		void OnEvent(Event& e) override;

	private:
		bool OnKeyPressed(const KeyPressedEvent& e);
		bool OnMouseButtonPressed(const MouseButtonPressedEvent& e);

		//? Scene
		void NewScene();
		void OpenScene();
		void OpenScene(const std::filesystem::path& path);
		void SaveSceneAs();
		void SaveScene();
		void SerializeScene(Ref<Scene> scene, const std::filesystem::path& path);

		void OnScenePlay();
		void OnSceneStop();
		void OnScenePause();
		void OnSceneSimulate();

		//? UI
		void UI_Toolbar();


	private:
		//? Temp
		ShaderLibrary m_ShaderLib;
		Ref<Shader> m_Shader;
		Ref<VertexArray> m_SquareVA;
		Ref<Texture2D>  m_TextureNull, m_TextureError, m_Background, m_IndustrialTilemap, m_CubeHead;

		Ref<Texture2D> m_IconPlay;
		Ref<Texture2D> m_IconStop;
		Ref<Texture2D> m_IconPause;

		Ref<SubTexture2D>  m_SubTextureNull, m_SubTextureError;
		Ref<SubTexture2D>  m_TileDirtTop, m_TileDirtCenter, m_TileDirtLeftCenter, m_TileDirtRightCenter, m_TileDirtMid;
		Ref<SubTexture2D>  m_TileWaterTop, m_TileWaterCenter;
		Ref<SubTexture2D>  m_TileChest;

		Ref<Framebuffer> m_Framebuffer;
		Ref<Scene> m_EditorScene;
		Ref<Scene> m_ActiveScene;
		SceneState m_SceneState = SceneState::Edit;

		Entity m_SquareEntity;
		Entity m_CameraEntity;
		Entity m_SecondCameraEntity;
		Entity m_HoveredEntity;
		Entity m_SelectedEntity;
		bool m_PrimaryCamera = true;

		EditorCamera m_EditorCamera;

		const float sizeMultiplier = 0.01f;

		int m_LoopCounter = 0;
		std::string m_FPS = "";

		bool m_ViewportFocused = false;
		bool m_ViewportHovered = false;

		OrthographicCameraController m_CameraController;
		Player m_Player;

		glm::vec4 m_SquareColor = { 0.2f,0.3f,0.7f,1.0f };
		glm::vec2 m_ViewportSize = { 0.0f,0.0f };
		glm::vec2 m_ViewportBounds[2];
		ParticleSystem m_ParticleSystem;
		ParticleProperties m_Particle;
		WorldGeneration m_World;
		std::unordered_map<glm::vec4, Ref<SubTexture2D>, vec4Hash, vec4Equal> m_TextureMap;
		int m_GuizmoType = -1;

		std::filesystem::path m_EditorScenePath;

		//. Panels
		SceneHierarchyPanel m_ScHiPanel;
		ContentBrowserPanel m_ContBrowPanel;
		WindowPanel m_WindowPanel;

		//. Systems
		FileSystem m_FSystem;

		//. ImGui Errors
		bool m_NoEntitySelected = false;
	};
}
