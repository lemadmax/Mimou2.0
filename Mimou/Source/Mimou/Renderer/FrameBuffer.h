#pragma once

#include "Mimou/Core.h"

namespace Mimou
{
	enum class FBFormat
	{
		None = 0,

		INT,
		RGBA,
		DEPTH_STENCIL,

	};

	struct FrameBufferSpecification
	{
		uint32_t Width, Height;
		FBFormat Format;
	};

	class FrameBuffer
	{
	public:
		virtual ~FrameBuffer() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual uint32_t GetColorAttachmentTexID() const = 0;
		virtual uint32_t GetColorAttachmentTexIDByIdx(uint32_t Idx) const = 0;
		virtual uint32_t GetDepthStencilAttachTexID() const = 0;

		virtual void OnUpdate(int Idx, uint32_t Width, uint32_t Height) = 0;
		virtual void Resize(uint32_t Width, uint32_t Height) = 0;

		virtual void Add(const FrameBufferSpecification& Spec) = 0;
		virtual int ReadPixelInt(int Idx, uint32_t x, uint32_t y) = 0;

		virtual void ClearAttachmentInt(int Idx, int Value) = 0;

		static Ref<FrameBuffer> Create(const FrameBufferSpecification& Spec);


	protected:
		std::vector<FrameBufferSpecification> m_Specs;
	};
}