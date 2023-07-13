#include "Player.h"

void Player::OnUpdate(LWEngine::Timestep ts)
{
	//. Player MOVEMENTS
	if (LWEngine::Input::IsKeyPressed(LWE_KEY_RIGHT))
	{
		m_PlayerPosition.x += m_PlayerTranslationSpeed * ts;
		//m_PlayerPosition.y += m_PlayerTranslationSpeed * ts;
	}

	else if (LWEngine::Input::IsKeyPressed(LWE_KEY_LEFT))
	{
		m_PlayerPosition.x -= m_PlayerTranslationSpeed * ts;
		//m_PlayerPosition.y -= m_PlayerTranslationSpeed * ts;
	}

	if (LWEngine::Input::IsKeyPressed(LWE_KEY_UP))
	{
		//m_PlayerPosition.x += m_PlayerTranslationSpeed * ts;
		m_PlayerPosition.y += m_PlayerTranslationSpeed * ts;
	}
	else if (LWEngine::Input::IsKeyPressed(LWE_KEY_DOWN))
	{
		//m_PlayerPosition.x -= m_PlayerTranslationSpeed * ts;
		m_PlayerPosition.y -= m_PlayerTranslationSpeed * ts;
	}
}
