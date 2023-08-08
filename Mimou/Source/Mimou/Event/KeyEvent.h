#pragma once

#include "EventBase.h"

namespace Mimou {

	class ME_API KeyEvent : public EventBase
	{
		EVENT_CATEGORY(EEventCategory::EventCategoryKeyboard | EEventCategory::EventCategoryInput)
	public:
		inline int GetKeyCode() { return m_KeyCode; }

	protected:
		KeyEvent(int KeyCode) : m_KeyCode(KeyCode) {}
		int m_KeyCode;
	};

	class ME_API KeyPressedEvent : public KeyEvent
	{
		EVENT_TYPE(KeyPressed)
	public:
		KeyPressedEvent(int KeyCode, int RepeatCount)
			: KeyEvent(KeyCode), m_RepeatCount(RepeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent -- [KeyCode:" << KeyCode << ", repeats:" << m_RepeatCount << "]";
			return ss.str();
		}

	private:
		int m_RepeatCount;
	};
}
