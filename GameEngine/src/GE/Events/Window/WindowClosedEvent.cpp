#include "gepch.h"
#include "WindowClosedEvent.h"

namespace GE
{
	WindowClosedEvent::WindowClosedEvent()
		: Event(EventType::WindowClose, EventCategory::Application)
	{
	}
	std::string WindowClosedEvent::toString() const
	{
		return "WindowClosedEvent";
	}
}