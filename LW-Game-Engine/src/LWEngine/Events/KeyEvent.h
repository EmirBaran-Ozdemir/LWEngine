#pragma once

#include "LWEngine/Events/Event.h"
#include "LWEngine/Core/KeyCodes.h"

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
		KeyEvent(const KeyCode keycode)
			: m_KeyCode(keycode){}

		KeyCode m_KeyCode;
	};

	//. KeyPressed class for holding the key long time
	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(const KeyCode keycode, const uint16_t repeatCount)
			: KeyEvent(keycode), m_repeatCount(repeatCount) {}
		uint16_t GetRepeatCount() const { return m_repeatCount; }
		
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_repeatCount << " times)";
			return ss.str();
		}
		
		EVENT_CLASS_TYPE(KeyPressed);
	private:
		uint16_t m_repeatCount;
	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(const KeyCode keycode)
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
		KeyReleasedEvent(const KeyCode keycode)
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