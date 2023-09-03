#pragma once

namespace Mimou
{
	class Texture
	{
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetData(void* Data, uint32_t Size) = 0;

		virtual void Bind(uint32_t Slot = 0) const = 0;
	};
}