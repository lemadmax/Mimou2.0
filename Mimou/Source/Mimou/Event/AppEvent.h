#pragma once

#include "EventBase.h"

namespace Mimou
{

	class ME_API AppEvent : public EventBase
	{
		EVENT_CATEGORY(EEventCategory::EventCategoryApplication)
	public:
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
		EVENT_TYPE(WindowClose)
	public:
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
		EVENT_TYPE(WindowResize)
	public:
		WindowResizeEvent(std::string Title, UINT32 Width, UINT32 Height)
			: AppEvent(Title), m_Width(Width), m_Height(Height) {}

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
		EVENT_TYPE(WindowFocus)
	public:
		//WindowFocusEvent(std::string Title, )
	};
}