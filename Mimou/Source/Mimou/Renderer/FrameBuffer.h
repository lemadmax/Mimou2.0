#pragma once

#include "Mimou/Core.h"

#include "glm/glm.hpp"

namespace Mimou
{
	enum class FBFormat
	{
		None = 0,

		INT,
		RGBA,
		DEPTH_STENCIL,

	};

	struct FBAttachmentSpecification
	{
		FBFormat Format;
	};

	struct FrameBufferSpecification
	{
		uint32_t Width, Height;
		std::vector<FBAttachmentSpecification> Attachments;

		//FrameBufferSpecification(uint32_t InWidth, uint32_t InHeight, std::initializer_list<FBAttachmentSpecification> Initializer)
		//	: Width(InWidth), Height(InHeight)
		//{

		//}
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

		virtual void OnUpdate(uint32_t Width, uint32_t Height) = 0;
		virtual void Resize(uint32_t Width, uint32_t Height) = 0;

		virtual int ReadPixelInt(int Idx, uint32_t x, uint32_t y) = 0;

		virtual void ClearAttachmentInt(int Idx, int Value) = 0;
		virtual void ClearAttachmentColor(int Idx, glm::vec4 Value) = 0;

		static Ref<FrameBuffer> Create(const FrameBufferSpecification& Spec);

		void Add(const FBAttachmentSpecification& Spec);

	protected:
		FrameBufferSpecification m_Spec;
	};
}