#pragma once
#include "mepch.h"
#include "Mimou/Core.h"

namespace Mimou {

	enum class EEventType
	{
		None = 0,
		KeyPressed,
		KeyReleased,
		KeyTyped,
		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		MouseScrolled,
		WindowClose,
		WindowResize,
		WindowFocus,
		WindowMoved,
	};

	enum EEventCategory
	{
		None = 0,
		EventCategoryApplication	= BIT(1),
		EventCategoryInput			= BIT(2),
		EventCategoryKeyboard		= BIT(3),
		EventCategoryMouse			= BIT(4),
		EventCategoryMouseButton	= BIT(5)
	};

#define EVENT_CATEGORY(Category) virtual int GetCategoryFlags() const override { return Category; }

#define EVENT_TYPE(Type) static EEventType StaticType() { return EEventType::Type; } \
							virtual EEventType GetEventType() const override { return StaticType(); } \
							virtual const char* GetName() const override { return #Type; }


	class ME_API EventBase
	{
	public:
		EventBase() {}
		virtual ~EventBase() {}

	public:
		virtual EEventType GetEventType() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual const char* GetName() const = 0;
		virtual std::string ToString() const { return GetName(); }

		bool IsInCategory(EEventCategory Category)
		{
			return GetCategoryFlags() & Category;
		}

		bool bHandled = false;
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(EventBase& Event) : m_Event(Event) {}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::StaticType())
			{
				m_Event.bHandled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:
		EventBase& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const EventBase& e)
	{
		return os << e.ToString();
	}
}