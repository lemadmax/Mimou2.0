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

		static Ref<FrameBuffer> Create(const FrameBufferSpecification& Spec);
	};
}