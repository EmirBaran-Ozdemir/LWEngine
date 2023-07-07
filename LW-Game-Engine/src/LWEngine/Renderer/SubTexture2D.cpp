#include "lwpch.h"
#include "SubTexture2D.h"


namespace LWEngine {

	SubTexture2D::SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max)
		:m_Texture(texture)
	{
		m_TexCoords[0] = { min.x,min.y };
		m_TexCoords[1] = { max.x,min.y };
		m_TexCoords[2] = { max.x,max.y };
		m_TexCoords[3] = { min.x,max.y };
	}
	Ref<SubTexture2D> SubTexture2D::CreateFromCoords(const Ref<Texture2D>& texture, const glm::vec2 coords, const glm::vec2 spriteSize, float offset)
	{
		glm::vec2 min = { (coords.x * (spriteSize.x + offset)) / texture->GetWidth(), (coords.y * (spriteSize.y + offset)) / texture->GetHeight() };
		glm::vec2 max = { (coords.x * (spriteSize.x + offset) + spriteSize.x) / texture->GetWidth(), (coords.y * (spriteSize.y + offset) + spriteSize.y) / texture->GetHeight() };
		return CreateRef<SubTexture2D>(texture, min, max);
	}

}

