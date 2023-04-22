#pragma once

#include "Event.h"

#include <sstream>

namespace LWEngine
{
	//. Base class for all events. Constructor is protected so it is kind of abstract class	
	class LWE_API KeyEvent : public Event
	{
	public: 
		inline int GetKeyCode() const { return m_KeyCode; }
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int keycode)
			: m_KeyCode(keycode){}

		int m_KeyCode;
	};

	//. KeyPressed class for holding the key long time
	class LWE_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_repeatCount(repeatCount) {}
		inline int GetRepeatCount() const { return m_repeatCount; }
		
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_repeatCount << " times)";
			return ss.str();
		}
		
		EVENT_CLASS_TYPE(KeyPressed);
	private:
		int m_repeatCount;
	};

	class LWE_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode){}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased);

	};
}