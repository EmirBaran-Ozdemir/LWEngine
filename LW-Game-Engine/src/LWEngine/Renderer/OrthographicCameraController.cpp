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
		LWE_PROFILE_FUNCTION();

		//. CAMERA MOVEMENTS
		if (Input::IsKeyPressed(LWE_KEY_RIGHT))
		{
			m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}

		else if (Input::IsKeyPressed(LWE_KEY_LEFT))
		{
			m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}

		if (Input::IsKeyPressed(LWE_KEY_UP))
		{
			m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(LWE_KEY_DOWN))
		{
			m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}

		//if (Input::IsKeyPressed(LWE_KEY_SPACE))
		//	m_CameraPosition.y += (m_CameraTranslationSpeed + m_CameraAcceleration) * ts;
		//else if (Input::IsKeyPressed(LWE_KEY_LEFT_SHIFT))
		//	m_CameraPosition.y -= (m_CameraTranslationSpeed + m_CameraAcceleration) * ts;
		
		m_Camera.SetPosition(m_CameraPosition);


		//. CAMERA ROTATIONS
		if (Input::IsKeyPressed(LWE_KEY_Q))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (Input::IsKeyPressed(LWE_KEY_E))
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		if (m_CameraRotation > 180.0f)
			m_CameraRotation -= 360.0f;
		else if (m_CameraRotation <= -180.0f)
			m_CameraRotation += 360.0f;

		m_Camera.SetRotation(m_CameraRotation);

		m_CameraTranslationSpeed = m_ZoomLevel;

	}
	
	void OrthographicCameraController::OnEvent(Event& e)
	{
		LWE_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(LWE_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(LWE_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	
	}
	
	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		LWE_PROFILE_FUNCTION();

		m_ZoomLevel -= e.GetYOffset() * 0.1f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
	
	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		LWE_PROFILE_FUNCTION();

		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
}

