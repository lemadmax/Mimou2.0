#pragma once

#include "Mimou/Window/Window.h"
#include "Mimou/Renderer/GraphicsContext.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Mimou
{
	class ME_API WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& Props);
		~WindowsWindow();

		virtual void OnUpdate() override;

		virtual inline UINT32 GetWidth() const override { return m_Data.Width; }
		virtual inline UINT32 GetHeight() const override { return m_Data.Height; }

		virtual void SetEventCallback(const EventCallbackFn& Callback) override { m_Data.EventCallback = Callback; }
		virtual void SetVSync(bool Enabled) override;
		virtual bool IsVSync() const override;
		virtual inline void* GetNativeWindow() const { return m_Window; }

	private:
		virtual void Init(const WindowProps& Props);
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;

		struct WindowData
		{
			std::string Title;
			UINT32 Width, Height;
			bool bVSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}