#pragma once

#include "LWEngine.h"
#include <stb_image/stb_image.h>
#include <glad/glad.h>

class WorldGeneration
{
public:
	explicit WorldGeneration(const std::string& path);

	float GetWidth() const { return m_Width; }
	float GetHeight() const { return m_Height; }
	std::vector<glm::vec4> GetTiles() const { return m_MapTiles; }
private:
	std::vector<glm::vec4> m_MapTiles;
	int m_Width = 0.0f;
	int m_Height = 0.0f;
	int m_Channels;
};
