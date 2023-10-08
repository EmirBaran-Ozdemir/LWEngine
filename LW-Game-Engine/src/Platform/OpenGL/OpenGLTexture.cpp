#include "lwpch.h"
#include "Platform/OpenGL/OpenGLTexture.h"

#include <stb_image.h>

namespace LWEngine {


	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
		: m_Width(width), m_Height(height)
	{
		LWE_PROFILE_FUNCTION();

		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		:m_Path(path)
	{
		LWE_PROFILE_FUNCTION();

		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = nullptr;
		{
			LWE_PROFILE_SCOPE("stbi_load - OpenGLTexture2D::OpenGLTexture2D(const std::string&)");

			data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		}
		
		LWE_CORE_ASSERT(data, "STB_IMAGE::LOAD_FAILED");

		m_Width = width;
		m_Height = height;

		if (channels == 1)
		{
			m_InternalFormat = GL_R8;
			m_DataFormat = GL_R;
		}
		else if (channels == 1)
		{
			m_InternalFormat = GL_RG8;
			m_DataFormat = GL_RG;
		}
		else if (channels == 3)
		{
			m_InternalFormat = GL_RGB8;
			m_DataFormat = GL_RGB;
		}
		else if (channels == 4)
		{
			m_InternalFormat = GL_RGBA8;
			m_DataFormat = GL_RGBA;
		}

		LWE_CORE_ASSERT(m_InternalFormat & m_DataFormat, "STBI_IMAGE::FORMAT_NOT_SUPPORTED");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}


	OpenGLTexture2D::~OpenGLTexture2D()
	{
		LWE_PROFILE_FUNCTION();

		glDeleteTextures(1, &m_RendererID);
	}


	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		LWE_PROFILE_FUNCTION();

		uint32_t bytePerPixel = m_DataFormat == GL_RGBA ? 4 : 3;
		LWE_CORE_ASSERT(size = m_Width * m_Height * bytePerPixel, "ERROR::SET_DATA::DATA_MUST_BE_ENTIRE_TEXTURE");
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture2D::Bind(uint32_t unit) const
	{
		LWE_PROFILE_FUNCTION();

		glBindTextureUnit(unit, m_RendererID);
	}

}

