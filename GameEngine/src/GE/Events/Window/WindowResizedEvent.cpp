#include "gepch.h"
#include "WindowResizedEvent.h"

namespace GE
{
	WindowResizedEvent::WindowResizedEvent(const uint32 width, const uint32 height)
		: Event(EventType::WindowResize, EventCategory::Application), width(width), height(height)
	{
	}
	std::string WindowResizedEvent::toString() const
	{
		return "WindowResized: w(" + STRINGY(width) + "), h(" + STRINGY(height) + ")";
	}
	uint32 WindowResizedEvent::getWidth() const
	{
		return width;
	}
	uint32 WindowResizedEvent::getHeight() const
	{
		return height;
	}
}