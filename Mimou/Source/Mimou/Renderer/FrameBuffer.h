#pragma once

#include "Mimou/Core.h"

namespace Mimou
{
	struct FrameBufferSpecification
	{
		uint32_t Width, Height;

	};

	class FrameBuffer
	{
	public:
		virtual ~FrameBuffer() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual uint32_t GetColorAttachmentTexID() const = 0;
		virtual uint32_t GetDepthStencilAttachTexID() const = 0;

		virtual void OnUpdate(uint32_t Width, uint32_t Height) = 0;
		virtual void Resize(uint32_t Width, uint32_t Height) = 0;

		static Ref<FrameBuffer> Create(const FrameBufferSpecification& Spec);
	};
}