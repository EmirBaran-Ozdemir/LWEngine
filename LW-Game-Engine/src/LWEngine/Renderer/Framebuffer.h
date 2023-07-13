#pragma once
#include "LWEngine/Core/Core.h"

namespace LWEngine {

	struct FramebufferSpecification
	{
		uint32_t Width, Height;
		uint32_t Samples = 1;

		bool SwapChainTarget = false; // Swap rendering directly on screen
	};

	class Framebuffer
	{
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		
		virtual uint32_t GetColorAttachmentRendererID() const = 0;

		static Ref<Framebuffer> Create(const FramebufferSpecification& spec);
		virtual const FramebufferSpecification& GetSpecification() const = 0;

	};

}