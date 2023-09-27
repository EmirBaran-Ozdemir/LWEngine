#include "lwpch.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

#include <glad/glad.h>

namespace LWEngine {

	static uint32_t s_MaxFbufferSize;

	namespace Utils {

		static GLenum TextureTarget(bool mutlisampled)
		{
			return mutlisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
		}

		static void BindTexture(bool mutlisampled, uint32_t id)
		{
			glBindTexture(TextureTarget(mutlisampled), id);
		}

		static void CreateTextures(bool mutlisampled, uint32_t* data, uint32_t size)
		{
			glCreateTextures(TextureTarget(mutlisampled), size, data);
		}

		static bool IsDepthFormat(FbufferTexFormat format)
		{
			switch (format)
			{
				case FbufferTexFormat::DEPTH24STENCIL8:		return true;
			}
			return false;
		}

		static uint32_t GetMaxFbufferSize()
		{
			GLint maxFramebufferSize;
			glGetIntegerv(GL_MAX_FRAMEBUFFER_WIDTH, &maxFramebufferSize);
			return static_cast<uint32_t>(maxFramebufferSize);
		}

		static void AttachColorTexture(uint32_t id, int samples, GLenum internalFormat, GLenum format, uint32_t width, uint32_t height, int index)
		{
			bool mutlisampled = samples > 1;
			if (mutlisampled)
			{
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internalFormat, width, height, GL_FALSE);
			}
			else
			{
				glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(mutlisampled), id, 0);
			
			GLenum framebufferError = glGetError();
			if (framebufferError != GL_NO_ERROR) {
				LWE_CORE_ERROR("OpenGL Error in framebuffer creation: {0}", framebufferError);
			}
		}

		static void AttachDepthTexture(uint32_t id, int samples, GLenum format, GLenum attachmentType, uint32_t width, uint32_t height)
		{
			bool mutlisampled = samples > 1;
			if (mutlisampled)
			{
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
			}
			else
			{
				glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);
				//glTexImage2D(GL_TEXTURE_2D, 1, format, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}
			glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(mutlisampled), id, 0);
		}

		static GLenum LWEngineTextureToGL(FbufferTexFormat fbTexFormat)
		{
			switch (fbTexFormat)
			{
				case FbufferTexFormat::RGBA8:				return GL_RGBA8;
				case FbufferTexFormat::RED_INT:				return GL_RED_INTEGER;
				case FbufferTexFormat::DEPTH24STENCIL8:		return GL_DEPTH24_STENCIL8;
				default:
					LWE_CORE_ASSERT(false, "ERROR::ENUM_CONVERT::UNKNOWN_FORMAT");
			}
		}
	}

	OpenGLFramebuffer::OpenGLFramebuffer(const FbufferSpec& spec)
		:m_Specification(spec)
	{
		s_MaxFbufferSize = Utils::GetMaxFbufferSize();
		for (auto format : m_Specification.Attachments.Attachments)
		{
			if (!Utils::IsDepthFormat(format.TextureFormat))
				m_ColorAttachmentSpecs.emplace_back(format);
			else
				m_DepthAttachmentSpec = format;
		}
		Recreate(); //If status isinvalid recreate
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
		glDeleteTextures(m_ColorAttachmentIds.size(), m_ColorAttachmentIds.data());
		glDeleteTextures(1, &m_DepthAttachment);
	}

	void OpenGLFramebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		glViewport(0, 0, m_Specification.Width, m_Specification.Height);
	}

	void OpenGLFramebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::Resize(uint32_t width, uint32_t height)
	{
		if (width <= 0 || height <= 0 || width > s_MaxFbufferSize || height > s_MaxFbufferSize)
		{
			LWE_CORE_ERROR("ERROR::FRAMEBUFFER::SIZE_IS_NOT_VALID::W:{0}_H:{1}", width, height);
			return;
		}
		m_Specification.Width = width;
		m_Specification.Height = height;
		Recreate();
	}

	int OpenGLFramebuffer::ReadPixel(uint32_t index, int x, int y, int height, int width)
	{
		LWE_CORE_ASSERT(index < m_ColorAttachmentIds.size(), "ERROR::PIXEL_READ::INDEX_{0}_OUT_OF_BOUNDS", index);
		glReadBuffer(GL_COLOR_ATTACHMENT0 + index);
		int pixelData;
		glReadPixels(x, y, height, width, GL_RED_INTEGER, GL_INT, &pixelData);
		return pixelData;
	}

	void OpenGLFramebuffer::ClearColorAttach(uint32_t index, int value)
	{
		LWE_CORE_ASSERT(index < m_ColorAttachmentIds.size(), "ERROR::CLEAR_COLOR_ATTACH::INDEX_{0}_OUT_OF_BOUNDS", index);
		auto& spec = m_ColorAttachmentSpecs[index];
		glClearTexImage(m_ColorAttachmentIds[index], 0, Utils::LWEngineTextureToGL(spec.TextureFormat), GL_INT, &value);
	}

	void OpenGLFramebuffer::Recreate()
	{
		if (m_RendererID)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glDeleteTextures(m_ColorAttachmentIds.size(), m_ColorAttachmentIds.data());
			glDeleteTextures(1, &m_DepthAttachment);

			m_ColorAttachmentIds.clear();
			m_DepthAttachment = 0;

		}

		glCreateFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		bool mutlisampled = m_Specification.Samples > 1;
		//. Attachments
		if (m_ColorAttachmentSpecs.size())
		{
			m_ColorAttachmentIds.resize(m_ColorAttachmentSpecs.size());

			Utils::CreateTextures(mutlisampled, m_ColorAttachmentIds.data(), m_ColorAttachmentIds.size());
			GLenum textureError = glGetError();
			if (textureError != GL_NO_ERROR) {
				LWE_CORE_ERROR("OpenGL Error in texture creation: {0}", textureError);
			}
			for (size_t i = 0; i < m_ColorAttachmentIds.size(); i++)
			{
				Utils::BindTexture(mutlisampled, m_ColorAttachmentIds[i]);
				switch (m_ColorAttachmentSpecs[i].TextureFormat)
				{
					case FbufferTexFormat::RGBA8:
						Utils::AttachColorTexture(m_ColorAttachmentIds[i], m_Specification.Samples, GL_RGBA8,GL_RGBA, m_Specification.Width, m_Specification.Height, i);
						break;
					case FbufferTexFormat::RED_INT:
						Utils::AttachColorTexture(m_ColorAttachmentIds[i], m_Specification.Samples, GL_R32I, GL_RED_INTEGER, m_Specification.Width, m_Specification.Height, i);
						break;
					default:
						LWE_CORE_ASSERT(false, "ERROR::FRAMEBUFFER::TEXTURE_FORMAT_IS_NOT_VALID");
				}
			}

		}
		
		if (m_DepthAttachmentSpec.TextureFormat != FbufferTexFormat::None)
		{
			Utils::CreateTextures(mutlisampled, &m_DepthAttachment, 1);
			Utils::BindTexture(mutlisampled, m_DepthAttachment);
			switch (m_DepthAttachmentSpec.TextureFormat)
			{
				case FbufferTexFormat::DEPTH24STENCIL8:
					Utils::AttachDepthTexture(m_DepthAttachment, m_Specification.Samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, m_Specification.Width, m_Specification.Height);
					break;
					//case FbufferTexFormat::DEPTH32F:
					//	Utils::AttachDepthTexture(mutlisampled, m_DepthAttachment, GL_DEPTH_COMPONENT32F, m_Specification.Width, m_Specification.Height);
					break;
				default:
					LWE_CORE_ASSERT(false, "ERROR::FRAMEBUFFER::TEXTURE_FORMAT_IS_NOT_VALID");
			}
		}

		if (m_ColorAttachmentIds.size() > 1)
		{
			LWE_CORE_ASSERT(m_ColorAttachmentIds.size() <= 4, "ERROR::FRAMEBUFFER::MAX_COLOR_ATTACHMENTS_IS_4");
			GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
			glDrawBuffers(m_ColorAttachmentIds.size(), buffers);
		}
		else if (m_ColorAttachmentIds.empty())
		{
			glDrawBuffer(GL_NONE);
		}

		LWE_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "ERROR::GL_FRAMEBUFFER::FRAMEBUFFER_INCOMPLETE");
		GLenum framebufferError = glGetError();
		if (framebufferError != GL_NO_ERROR) {
			LWE_CORE_ERROR("OpenGL Error in framebuffer creation: {0}", framebufferError);
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

}
