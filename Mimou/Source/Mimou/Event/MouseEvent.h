#pragma once
#include "Mimou/Event/EventBase.h"

namespace Mimou
{

	class ME_API MouseMoveEvent : public EventBase
	{
	public:
		EVENT_CATEGORY(EventCategoryMouse | EventCategoryInput)
		EVENT_TYPE(MouseMoved)
	public:
		MouseMoveEvent(double PosX, double PosY)
			: m_PosX(PosX), m_PosY(PosY) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseMoveEvent -- [Positon:(" << m_PosX << "," << m_PosY << ")]";
			return ss.str();
		}
		
	private:
		double m_PosX, m_PosY;
	};

	class ME_API MouseScrollEvent : public EventBase
	{
	public:
		EVENT_CATEGORY(EventCategoryMouse | EventCategoryInput)
		EVENT_TYPE(MouseScrolled)
	public:
		MouseScrollEvent(double OffsetX, double OffsetY)
			: m_OffsetX(OffsetX), m_OffsetY(OffsetY) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseScrollEvent -- [Offset:(" << m_OffsetX << "," << m_OffsetY << ")]";
			return ss.str();
		}

	private:
		double m_OffsetX, m_OffsetY;
	};

	class ME_API MouseButtonEvent : public EventBase
	{
	public:
		EVENT_CATEGORY(EventCategoryMouseButton | EventCategoryInput)
	public:
		MouseButtonEvent(INT32 Button)
			: m_Button(Button) {}

	protected:
		INT32 m_Button;
	};

	class ME_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		EVENT_TYPE(MouseButtonPressed)
	public:
		MouseButtonPressedEvent(INT32 Button)
			: MouseButtonEvent(Button) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonPressed -- [Button:" << m_Button << "]";
			return ss.str();
		}
	};

	class ME_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		EVENT_TYPE(MouseButtonReleased)
	public:
		MouseButtonReleasedEvent(INT32 Button)
			: MouseButtonEvent(Button) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonReleased -- [Button:" << m_Button << "]";
			return ss.str();
		}
	};

}