#pragma once

#include "LWEngine.h"
#include <stb_image/stb_image.h>
#include <glad/glad.h>

class WorldGeneration
{
public:
	WorldGeneration(const std::string& path);

	const float GetWidth() const { return m_Width; }
	const float GetHeight() const { return m_Height; }
	const std::vector<glm::vec4> GetTiles() const { return m_MapTiles; }
private:
	std::vector<glm::vec4> m_MapTiles;
	float m_Width = 0.0f, m_Height = 0.0f;
	int m_Channels;
};
