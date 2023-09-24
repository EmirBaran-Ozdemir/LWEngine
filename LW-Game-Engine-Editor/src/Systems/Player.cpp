#include "Player.h"
#include "LWEngine/Core/KeyCodes.h"

void Player::OnUpdate(LWEngine::Timestep ts)
{
	//. Player MOVEMENTS
	if (LWEngine::Input::IsKeyPressed(LWEngine::Key::Right))
	{
		m_PlayerPosition.x += m_PlayerTranslationSpeed * ts;
		//m_PlayerPosition.y += m_PlayerTranslationSpeed * ts;
	}

	else if (LWEngine::Input::IsKeyPressed(LWEngine::Key::Left))
	{
		m_PlayerPosition.x -= m_PlayerTranslationSpeed * ts;
		//m_PlayerPosition.y -= m_PlayerTranslationSpeed * ts;
	}

	if (LWEngine::Input::IsKeyPressed(LWEngine::Key::Up))
	{
		//m_PlayerPosition.x += m_PlayerTranslationSpeed * ts;
		m_PlayerPosition.y += m_PlayerTranslationSpeed * ts;
	}
	else if (LWEngine::Input::IsKeyPressed(LWEngine::Key::Down))
	{
		//m_PlayerPosition.x -= m_PlayerTranslationSpeed * ts;
		m_PlayerPosition.y -= m_PlayerTranslationSpeed * ts;
	}
}
