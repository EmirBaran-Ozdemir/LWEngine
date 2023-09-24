#include "lwpch.h"
#include "LWEngine/Renderer/OrthographicCameraController.h"

#include "LWEngine/Core/Input.h"
#include "LWEngine/Core/KeyCodes.h"

namespace LWEngine {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio)
		:m_AspectRatio(aspectRatio), m_Bounds({ -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel }), m_Camera(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top)
	{

	}

	void OrthographicCameraController::OnUpdate(Timestep ts)

	{
		LWE_PROFILE_FUNCTION();

		//. CAMERA MOVEMENTS
		if (Input::IsKeyPressed(Key::A))
		{
			m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(Key::D))
		{
			m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}

		if (Input::IsKeyPressed(Key::W))
		{
			m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(Key::S))
		{
			m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}


		if (Input::IsKeyPressed(Key::Q))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (Input::IsKeyPressed(Key::E))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		if (m_CameraRotation > 180.0f)
			m_CameraRotation -= 360.0f;
		else if (m_CameraRotation <= -180.0f)
			m_CameraRotation += 360.0f;

		m_Camera.SetRotation(m_CameraRotation);

		m_Camera.SetPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel;

	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		LWE_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(LWE_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(LWE_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));

	}

	void OrthographicCameraController::Resize(float width, float height)
	{
		m_AspectRatio = width / height;
		CalculateView();
	}

	void OrthographicCameraController::CalculateView()
	{
		m_Bounds = { -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel };
		m_Camera.SetProjection(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top);
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		LWE_PROFILE_FUNCTION();

		m_ZoomLevel -= e.GetYOffset() * 0.1f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		CalculateView();
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		LWE_PROFILE_FUNCTION();

		Resize((float)e.GetWidth(), (float)e.GetHeight());
		CalculateView();
		return false;
	}
}

