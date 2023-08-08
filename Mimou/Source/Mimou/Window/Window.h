#pragma once

#include "mepch.h"
#include "Mimou/Core.h"
#include "Mimou/Event/EventBase.h"

namespace Mimou
{

	struct WindowProps
	{
		std::string Title;
		UINT32 Width;
		UINT32 Height;

		WindowProps(const std::string& Title = "Mimou Engine",
			UINT32 Width = 1280,
			UINT32 Height = 720) : Title(Title), Width(Width), Height(Height)
		{

		}
	};

	class ME_API Window
	{
	public:
		using EventCallbackFn = std::function<void(EventBase&)>;

		virtual ~Window() {}
		
		virtual void OnUpdate() = 0;

		virtual UINT32 GetWidth() const = 0;
		virtual UINT32 GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& Callback) = 0;
		virtual void SetVSync(bool Enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProps& Props = WindowProps());
	};
}