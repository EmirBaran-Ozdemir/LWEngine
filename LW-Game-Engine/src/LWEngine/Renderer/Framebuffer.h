#pragma once
#include "LWEngine/Core/Core.h"

namespace LWEngine {

	enum class FbufferTexFormat
	{
		None = 0,

		//? Color
		RGBA8,
		RGBA16F,

		//? Depth/Stencil
		DEPTH24STENCIL8,

		//? Defaults
		Depth = DEPTH24STENCIL8
	};

	struct FbufferTexSpec
	{
		FbufferTexSpec() = default;
		FbufferTexSpec(FbufferTexFormat format)
			: TextureFormat(format) {}

		FbufferTexFormat TextureFormat = FbufferTexFormat::None;
		//? Filtering
		//? Wrapping
	};

	struct FbufferAttachmentSpec
	{
		FbufferAttachmentSpec() = default;
		FbufferAttachmentSpec(std::initializer_list<FbufferTexSpec> attachments)
			: Attachments(attachments) {}

		std::vector<FbufferTexSpec> Attachments;
	};

	struct FbufferSpec
	{
		uint32_t Width = 0, Height = 0;
		uint32_t Samples = 1;
		FbufferAttachmentSpec Attachments;
		bool SwapChainTarget = false; // Swap rendering directly on screen
	};

	class Framebuffer
	{
	public:
		virtual ~Framebuffer() = default;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const = 0;

		static Ref<Framebuffer> Create(const FbufferSpec& spec);
		virtual const FbufferSpec& GetSpecification() const = 0;

	};

}
