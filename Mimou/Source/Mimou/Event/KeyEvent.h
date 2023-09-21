#pragma once

#include "EventBase.h"

namespace Mimou {

	class ME_API KeyEvent : public EventBase
	{
	public:
		EVENT_CATEGORY(EEventCategory::EventCategoryKeyboard | EEventCategory::EventCategoryInput)
		inline const int GetKeyCode() const { return m_KeyCode; }

	protected:
		KeyEvent(int KeyCode) : m_KeyCode(KeyCode) {}
		int m_KeyCode;
	};

	class ME_API KeyPressedEvent : public KeyEvent
	{
	public:
		EVENT_TYPE(KeyPressed)
		KeyPressedEvent(int KeyCode, int RepeatCount)
			: KeyEvent(KeyCode), m_RepeatCount(RepeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent -- [KeyCode:" << m_KeyCode << ", repeats:" << m_RepeatCount << "]";
			return ss.str();
		}

	private:
		int m_RepeatCount;
	};

	class ME_API KeyReleasedEvent : public KeyEvent
	{
	public:
		EVENT_TYPE(KeyReleased)
		KeyReleasedEvent(int KeyCode)
			: KeyEvent(KeyCode) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent -- [KeyCode:" << m_KeyCode << "]";
			return ss.str();
		}
	};

	class ME_API KeyTypedEvent : public KeyEvent
	{
	public:
		EVENT_TYPE(KeyTyped)
		KeyTypedEvent(int KeyCode)
			: KeyEvent(KeyCode) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyTypedEvent -- [KeyCode:" << m_KeyCode << "]";
			return ss.str();
		}
	};
}
