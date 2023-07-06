#pragma once

namespace LWEngine {

	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348


	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

#define LWE_KEY_SPACE           ::LWEngine::Key::Space
#define LWE_KEY_APOSTROPHE      ::LWEngine::Key::Apostrophe    /* ' */
#define LWE_KEY_COMMA           ::LWEngine::Key::Comma         /* , */
#define LWE_KEY_MINUS           ::LWEngine::Key::Minus         /* - */
#define LWE_KEY_PERIOD          ::LWEngine::Key::Period        /* . */
#define LWE_KEY_SLASH           ::LWEngine::Key::Slash         /* / */
#define LWE_KEY_0               ::LWEngine::Key::D0
#define LWE_KEY_1               ::LWEngine::Key::D1
#define LWE_KEY_2               ::LWEngine::Key::D2
#define LWE_KEY_3               ::LWEngine::Key::D3
#define LWE_KEY_4               ::LWEngine::Key::D4
#define LWE_KEY_5               ::LWEngine::Key::D5
#define LWE_KEY_6               ::LWEngine::Key::D6
#define LWE_KEY_7               ::LWEngine::Key::D7
#define LWE_KEY_8               ::LWEngine::Key::D8
#define LWE_KEY_9               ::LWEngine::Key::D9
#define LWE_KEY_SEMICOLON       ::LWEngine::Key::Semicolon     /* ; */
#define LWE_KEY_EQUAL           ::LWEngine::Key::Equal         /* = */
#define LWE_KEY_A               ::LWEngine::Key::A
#define LWE_KEY_B               ::LWEngine::Key::B
#define LWE_KEY_C               ::LWEngine::Key::C
#define LWE_KEY_D               ::LWEngine::Key::D
#define LWE_KEY_E               ::LWEngine::Key::E
#define LWE_KEY_F               ::LWEngine::Key::F
#define LWE_KEY_G               ::LWEngine::Key::G
#define LWE_KEY_H               ::LWEngine::Key::H
#define LWE_KEY_I               ::LWEngine::Key::I
#define LWE_KEY_J               ::LWEngine::Key::J
#define LWE_KEY_K               ::LWEngine::Key::K
#define LWE_KEY_L               ::LWEngine::Key::L
#define LWE_KEY_M               ::LWEngine::Key::M
#define LWE_KEY_N               ::LWEngine::Key::N
#define LWE_KEY_O               ::LWEngine::Key::O
#define LWE_KEY_P               ::LWEngine::Key::P
#define LWE_KEY_Q               ::LWEngine::Key::Q
#define LWE_KEY_R               ::LWEngine::Key::R
#define LWE_KEY_S               ::LWEngine::Key::S
#define LWE_KEY_T               ::LWEngine::Key::T
#define LWE_KEY_U               ::LWEngine::Key::U
#define LWE_KEY_V               ::LWEngine::Key::V
#define LWE_KEY_W               ::LWEngine::Key::W
#define LWE_KEY_X               ::LWEngine::Key::X
#define LWE_KEY_Y               ::LWEngine::Key::Y
#define LWE_KEY_Z               ::LWEngine::Key::Z
#define LWE_KEY_LEFT_BRACKET    ::LWEngine::Key::LeftBracket   /* [ */
#define LWE_KEY_BACKSLASH       ::LWEngine::Key::Backslash     /* \ */
#define LWE_KEY_RIGHT_BRACKET   ::LWEngine::Key::RightBracket  /* ] */
#define LWE_KEY_GRAVE_ACCENT    ::LWEngine::Key::GraveAccent   /* ` */
#define LWE_KEY_WORLD_1         ::LWEngine::Key::World1        /* non-US #1 */
#define LWE_KEY_WORLD_2         ::LWEngine::Key::World2        /* non-US #2 */

/* Function keys */
#define LWE_KEY_ESCAPE          ::LWEngine::Key::Escape
#define LWE_KEY_ENTER           ::LWEngine::Key::Enter
#define LWE_KEY_TAB             ::LWEngine::Key::Tab
#define LWE_KEY_BACKSPACE       ::LWEngine::Key::Backspace
#define LWE_KEY_INSERT          ::LWEngine::Key::Insert
#define LWE_KEY_DELETE          ::LWEngine::Key::Delete
#define LWE_KEY_RIGHT           ::LWEngine::Key::Right
#define LWE_KEY_LEFT            ::LWEngine::Key::Left
#define LWE_KEY_DOWN            ::LWEngine::Key::Down
#define LWE_KEY_UP              ::LWEngine::Key::Up
#define LWE_KEY_PAGE_UP         ::LWEngine::Key::PageUp
#define LWE_KEY_PAGE_DOWN       ::LWEngine::Key::PageDown
#define LWE_KEY_HOME            ::LWEngine::Key::Home
#define LWE_KEY_END             ::LWEngine::Key::End
#define LWE_KEY_CAPS_LOCK       ::LWEngine::Key::CapsLock
#define LWE_KEY_SCROLL_LOCK     ::LWEngine::Key::ScrollLock
#define LWE_KEY_NUM_LOCK        ::LWEngine::Key::NumLock
#define LWE_KEY_PRINT_SCREEN    ::LWEngine::Key::PrintScreen
#define LWE_KEY_PAUSE           ::LWEngine::Key::Pause
#define LWE_KEY_F1              ::LWEngine::Key::F1
#define LWE_KEY_F2              ::LWEngine::Key::F2
#define LWE_KEY_F3              ::LWEngine::Key::F3
#define LWE_KEY_F4              ::LWEngine::Key::F4
#define LWE_KEY_F5              ::LWEngine::Key::F5
#define LWE_KEY_F6              ::LWEngine::Key::F6
#define LWE_KEY_F7              ::LWEngine::Key::F7
#define LWE_KEY_F8              ::LWEngine::Key::F8
#define LWE_KEY_F9              ::LWEngine::Key::F9
#define LWE_KEY_F10             ::LWEngine::Key::F10
#define LWE_KEY_F11             ::LWEngine::Key::F11
#define LWE_KEY_F12             ::LWEngine::Key::F12
#define LWE_KEY_F13             ::LWEngine::Key::F13
#define LWE_KEY_F14             ::LWEngine::Key::F14
#define LWE_KEY_F15             ::LWEngine::Key::F15
#define LWE_KEY_F16             ::LWEngine::Key::F16
#define LWE_KEY_F17             ::LWEngine::Key::F17
#define LWE_KEY_F18             ::LWEngine::Key::F18
#define LWE_KEY_F19             ::LWEngine::Key::F19
#define LWE_KEY_F20             ::LWEngine::Key::F20
#define LWE_KEY_F21             ::LWEngine::Key::F21
#define LWE_KEY_F22             ::LWEngine::Key::F22
#define LWE_KEY_F23             ::LWEngine::Key::F23
#define LWE_KEY_F24             ::LWEngine::Key::F24
#define LWE_KEY_F25             ::LWEngine::Key::F25

/* Keypad */
#define LWE_KEY_KP_0            ::LWEngine::Key::KP0
#define LWE_KEY_KP_1            ::LWEngine::Key::KP1
#define LWE_KEY_KP_2            ::LWEngine::Key::KP2
#define LWE_KEY_KP_3            ::LWEngine::Key::KP3
#define LWE_KEY_KP_4            ::LWEngine::Key::KP4
#define LWE_KEY_KP_5            ::LWEngine::Key::KP5
#define LWE_KEY_KP_6            ::LWEngine::Key::KP6
#define LWE_KEY_KP_7            ::LWEngine::Key::KP7
#define LWE_KEY_KP_8            ::LWEngine::Key::KP8
#define LWE_KEY_KP_9            ::LWEngine::Key::KP9
#define LWE_KEY_KP_DECIMAL      ::LWEngine::Key::KPDecimal
#define LWE_KEY_KP_DIVIDE       ::LWEngine::Key::KPDivide
#define LWE_KEY_KP_MULTIPLY     ::LWEngine::Key::KPMultiply
#define LWE_KEY_KP_SUBTRACT     ::LWEngine::Key::KPSubtract
#define LWE_KEY_KP_ADD          ::LWEngine::Key::KPAdd
#define LWE_KEY_KP_ENTER        ::LWEngine::Key::KPEnter
#define LWE_KEY_KP_EQUAL        ::LWEngine::Key::KPEqual

#define LWE_KEY_LEFT_SHIFT      ::LWEngine::Key::LeftShift
#define LWE_KEY_LEFT_CONTROL    ::LWEngine::Key::LeftControl
#define LWE_KEY_LEFT_ALT        ::LWEngine::Key::LeftAlt
#define LWE_KEY_LEFT_SUPER      ::LWEngine::Key::LeftSuper
#define LWE_KEY_RIGHT_SHIFT     ::LWEngine::Key::RightShift
#define LWE_KEY_RIGHT_CONTROL   ::LWEngine::Key::RightControl
#define LWE_KEY_RIGHT_ALT       ::LWEngine::Key::RightAlt
#define LWE_KEY_RIGHT_SUPER     ::LWEngine::Key::RightSuper
#define LWE_KEY_MENU            ::LWEngine::Key::Menu