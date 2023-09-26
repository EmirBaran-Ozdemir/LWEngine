#pragma once

#include "LWEngine/Renderer/Framebuffer.h"

namespace LWEngine {

	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FbufferSpec& spec);
		virtual ~OpenGLFramebuffer();

		virtual void Bind() override;
		virtual void Unbind() override;
		virtual void Resize(uint32_t width, uint32_t height) override;
		void Recreate();

		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const override { LWE_CORE_ASSERT(index < m_ColorAttachmentIds.size(), "ERROR::RENDERER::COLOR_INDEX_LESS_THAN_ATTACHMENT_IDS") return m_ColorAttachmentIds[index]; }

		virtual const FbufferSpec& GetSpecification() const override { return m_Specification; }

	private:
		uint32_t m_RendererID = 0;
		FbufferSpec m_Specification;

		std::vector<FbufferTexSpec> m_ColorAttachmentSpecs;
		FbufferTexSpec m_DepthAttachmentSpec = FbufferTexFormat::None;

		std::vector<uint32_t> m_ColorAttachmentIds;
		uint32_t m_DepthAttachment = 0;
	};
}
