#pragma once

#include "LWEngine/Renderer/OrthographicCamera.h"
#include "LWEngine/Core/Timestep.h"
#include "LWEngine/Events/ApplicationEvent.h"
#include "LWEngine/Events/MouseEvent.h"


namespace LWEngine {

	struct OrthographicCameraBounds
	{
		float Left, Right;
		float Bottom, Top;

		float GetWidth() { return Right - Left; }
		float GetHeight() { return Top - Bottom; }
	};


	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		void Resize(float width, float height);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }
		const OrthographicCameraBounds& GetBounds() const { return m_Bounds; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float zoomLevel) { m_ZoomLevel = zoomLevel; CalculateView(); }
	private:
		void CalculateView();
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCameraBounds m_Bounds;
		OrthographicCamera m_Camera;

		glm::vec3 m_CameraPosition = { 0.0f,0.0f,0.0f };
		float m_CameraTranslationSpeed = 5.0f;
		float m_CameraAcceleration = 0.01f;
		float m_CameraRotation = 0.0f;
		float m_CameraRotationSpeed = 60.0f;

	};
}