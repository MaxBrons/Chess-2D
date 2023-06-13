#pragma once

namespace C2DCore::EventSystem
{
	enum class EventType
	{
		None = 0,
		WindowClose,
		WindowResize,
		WindowFocus,
		WindowLostFocus,
		WindowMoved,
		KeyPressed,
		KeyReleased,
		KeyTyped,
		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		MouseScrolled
	};

#define EVENT_STATIC_TYPE_DEF(type) static EventType GetStaticEventType() { return EventType::##type; }\
									virtual EventType GetEventType() const override { return GetStaticEventType(); }\
									virtual const char* GetName() const override { return #type; }
	class Event
	{
	public:
		Event() = default;
		virtual ~Event() = default;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;

	public:
		bool Handled = false;
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		EVENT_STATIC_TYPE_DEF(WindowClose);
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(uint32_t width, uint32_t height)
			:Width(width), Height(height)
		{
		}
		EVENT_STATIC_TYPE_DEF(WindowResize);

	public:
		const float Width;
		const float Height;
	};

	class WindowFocusEvent : public Event
	{
	public:
		WindowFocusEvent() {}

		EVENT_STATIC_TYPE_DEF(WindowFocus);
	};

	class WindowLostFocusEvent : public Event
	{
	public:
		WindowLostFocusEvent() {}

		EVENT_STATIC_TYPE_DEF(WindowLostFocus);
	};

	class WindowMovedEvent : public Event
	{
	public:
		WindowMovedEvent(int x, int y)
			: PositionX(x), PositionY(y)
		{
		}

		EVENT_STATIC_TYPE_DEF(WindowMoved);

	public:
		const int PositionX;
		const int PositionY;
	};

	class KeyPressedEvent : public Event
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyCode(keycode), RepeatedCount(repeatCount)
		{
		}

		EVENT_STATIC_TYPE_DEF(KeyPressed);

	public:
		const int KeyCode;
		const int RepeatedCount;
	};

	class KeyReleasedEvent : public Event
	{
	public:
		KeyReleasedEvent(int keycode)
			:KeyCode(keycode)
		{
		}

		EVENT_STATIC_TYPE_DEF(KeyReleased);

	public:
		const int KeyCode;
	};

	class KeyTypedEvent : public Event
	{
	public:
		KeyTypedEvent(int keycode)
			: KeyCode(keycode)
		{
		}

		EVENT_STATIC_TYPE_DEF(KeyTyped);

	public:
		const int KeyCode;
	};

	class MouseButtonPressedEvent : public Event
	{
	public:
		MouseButtonPressedEvent(int button)
			:Button(button)
		{
		}

		EVENT_STATIC_TYPE_DEF(MouseButtonPressed);

	public:
		const int Button;
	};

	class MouseButtonReleasedEvent : public Event
	{
	public:
		MouseButtonReleasedEvent(int button)
			:Button(button)
		{
		}

		EVENT_STATIC_TYPE_DEF(MouseButtonReleased);

	public:
		const int Button;
	};

	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: MouseX(x), MouseY(y)
		{
		}

		EVENT_STATIC_TYPE_DEF(MouseMoved);

	public:
		const float MouseX;
		const float MouseY;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: XOffset(xOffset), YOffset(yOffset)
		{
		}

		EVENT_STATIC_TYPE_DEF(MouseScrolled);

	public:
		const float XOffset;
		const float YOffset;
	};
}
