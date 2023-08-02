#pragma once

#include "EventBase.h"

namespace Mimou {

	class ME_API KeyEvent : public EventBase
	{
		EVENT_CATEGORY(EEventCategory::EventCategoryKeyboard | EEventCategory::EventCategoryInput)
	public:
		inline int GetKeyCode() { return KeyCode; }

	protected:
		KeyEvent(int InKeyCode) : KeyCode(InKeyCode) {}
		int KeyCode;
	};

	class ME_API KeyPressedEvent : public KeyEvent
	{
		EVENT_TYPE(KeyPressed)
	public:
		KeyPressedEvent(int InKeyCode, int InRepeatCount)
			: KeyEvent(InKeyCode), RepeatCount(InRepeatCount) {}

		inline int GetRepeatCount() const { return RepeatCount; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent -- [KeyCode:" << KeyCode << ", repeats:" << RepeatCount << "]";
			return ss.str();
		}

	private:
		int RepeatCount;
	};
}
