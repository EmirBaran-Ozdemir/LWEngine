#pragma once

#include "LWEngine/Events/Event.h"
#include "LWEngine/Core/Input.h"

#include <sstream>

namespace LWEngine
{
	//. Base class for all events. Constructor is protected so it is kind of abstract class	
	class  KeyEvent : public Event
	{
	public: 
		KeyCode GetKeyCode() const { return m_KeyCode; }
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(KeyCode keycode)
			: m_KeyCode(keycode){}

		KeyCode m_KeyCode;
	};

	//. KeyPressed class for holding the key long time
	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(KeyCode keycode, int repeatCount)
			: KeyEvent(keycode), m_repeatCount(repeatCount) {}
		int GetRepeatCount() const { return m_repeatCount; }
		
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

	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(KeyCode keycode)
			: KeyEvent(keycode){}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped);
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(KeyCode keycode)
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