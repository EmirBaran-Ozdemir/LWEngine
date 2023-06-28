#include "lwpch.h"
#include "OrthographicCameraController.h"

#include "LWEngine/Core/Input.h"
#include "LWEngine/Core/KeyCodes.h"

namespace LWEngine {
	
	OrthographicCameraController::OrthographicCameraController(float aspectRatio)
		:m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
	{

	}
	
	void OrthographicCameraController::OnUpdate(Timestep ts)

	{
		//. CAMERA MOVEMENTS
		if (Input::IsKeyPressed(LWE_KEY_RIGHT) || Input::IsKeyPressed(LWE_KEY_D))
			m_CameraPosition.x += (m_CameraTranslationSpeed + m_CameraAcceleration) * ts;
		else if (Input::IsKeyPressed(LWE_KEY_LEFT) || Input::IsKeyPressed(LWE_KEY_A))
			m_CameraPosition.x -= (m_CameraTranslationSpeed + m_CameraAcceleration) * ts;

		if (Input::IsKeyPressed(LWE_KEY_UP) || Input::IsKeyPressed(LWE_KEY_W))
			m_CameraPosition.z -= (m_CameraTranslationSpeed + m_CameraAcceleration) * ts;
		else if (Input::IsKeyPressed(LWE_KEY_DOWN) || Input::IsKeyPressed(LWE_KEY_S))
			m_CameraPosition.z += (m_CameraTranslationSpeed + m_CameraAcceleration) * ts;

		if (Input::IsKeyPressed(LWE_KEY_SPACE))
			m_CameraPosition.y += (m_CameraTranslationSpeed + m_CameraAcceleration) * ts;
		else if (Input::IsKeyPressed(LWE_KEY_LEFT_SHIFT))
			m_CameraPosition.y -= (m_CameraTranslationSpeed + m_CameraAcceleration) * ts;
		
		m_Camera.SetPosition(m_CameraPosition);


		//. CAMERA ROTATIONS
		if (Input::IsKeyPressed(LWE_KEY_Q))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (Input::IsKeyPressed(LWE_KEY_E))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		m_Camera.SetRotation(m_CameraRotation);

		m_CameraTranslationSpeed = m_ZoomLevel;

	}
	
	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(LWE_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(LWE_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	
	}
	
	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() * 0.1f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
	
	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
}

