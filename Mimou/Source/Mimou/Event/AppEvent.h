#pragma once

#include "EventBase.h"

namespace Mimou
{

	class ME_API AppEvent : public EventBase
	{
	public:
		EVENT_CATEGORY(EEventCategory::EventCategoryApplication)
		AppEvent(std::string Title)
		{
			m_Title = Title;
		}

		inline std::string GetAppTitle() const { return m_Title; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "AppEvent -- [Title:" << m_Title << "]";
			return ss.str();
		}
	protected:
		std::string m_Title;
	};

	class ME_API WindowCloseEvent : public AppEvent
	{
	public:
		EVENT_TYPE(WindowClose)
		WindowCloseEvent(std::string Title)
			: AppEvent(Title) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowCloseEvent [Title:" << m_Title << "]";
			return ss.str();
		}
	};

	class ME_API WindowResizeEvent : public AppEvent
	{
	public:
		EVENT_TYPE(WindowResize)
		WindowResizeEvent(std::string Title, UINT32 Width, UINT32 Height)
			: AppEvent(Title), m_Width(Width), m_Height(Height) {}

		inline UINT32 GetWidth() const { return m_Width; }
		inline UINT32 GetHeight() const { return m_Height; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowResizeEvent [Title:" << m_Title << ", Width: " << m_Width << ", Height: " << m_Height << "]";
			return ss.str();
		}
	private:
		UINT32 m_Width, m_Height;
	};

	class ME_API WindowFocusEvent : public AppEvent
	{
	public:
		EVENT_TYPE(WindowFocus)
		WindowFocusEvent(std::string Title, INT32 Focused)
			: AppEvent(Title), m_Focused(Focused) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowFocusEvent [Title:" << m_Title << ", Focused: " << m_Focused << "]";
			return ss.str();
		}
	private:
		bool m_Focused;
	};

	class ME_API WindowMoveEvent : public AppEvent
	{
	public:
		EVENT_TYPE(WindowMoved)
		WindowMoveEvent(std::string Title, INT32 PosX, INT32 PosY)
			: AppEvent(Title), m_PosX(PosX), m_PosY(PosY) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowMoveEvent [Title:" << m_Title << ", PosX:" << m_PosX << ", PosY:" << m_PosY << "]";
			return ss.str();
		}
	private:
		INT32 m_PosX, m_PosY;
	};
}