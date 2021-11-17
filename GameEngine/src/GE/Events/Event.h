#ifndef GE_EVENTC
#define GE_EVENTC
#include "gepch.h"
#include "Object.h"

namespace GE
{
	enum class EventType
	{
		WindowResize, WindowClose,
		KeyPressed, KeyReleased, KeyHeld,
		MouseButPressed, MouseButReleased, MouseMoved, MouseScrolled
	};

	enum class EventCategory
	{
		Application, Keyboard, Mouse
	};

	inline std::string toString(EventCategory& cat)
	{
		switch (cat)
		{
		case EventCategory::Application: return "EventCategory::Application";
		case EventCategory::Keyboard:	return "EverntCatehory::Keyboard";
		case EventCategory::Mouse:		return "EventCategory::Mouse";
		}
	}

	/**
	* Event handler class acts as a dispatcher for glfw Events
	* which will be implemented via callback functions.
	* EventHandler will be a singletone class
	*/

	class Event : public Object
	{
	public:
		EventType getType() const;
		EventCategory getCategory() const;
		virtual std::string toString() const override = 0;
		bool isHandled() { return handled; }
		void setHandled() { this->handled = true; }
	private:
		EventType type;
		EventCategory category;
		bool handled = false;
	protected:
		Event(const EventType& type, const EventCategory& cat);
	};
}
#endif // !GE_EVENT

