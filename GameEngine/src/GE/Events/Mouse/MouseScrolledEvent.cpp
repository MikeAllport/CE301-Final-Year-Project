#include "gepch.h"
#include "MouseScrolledEvent.h"

namespace GE
{
	MouseScrolledEvent::MouseScrolledEvent(const double offsetX, const double offsetY):
		Event(EventType::MouseScrolled, EventCategory::Mouse),
		offsetX(offsetX), offsetY(offsetY)
	{
	}
	double MouseScrolledEvent::getOffsetX()
	{
		return offsetX;
	}
	double MouseScrolledEvent::getOffsetY()
	{
		return offsetY;
	}
	std::string MouseScrolledEvent::toString() const
	{
		return "MouseScrolledEvent: offsetX = " + STRINGY(offsetX) +
			", offsetY = " + STRINGY(offsetY);
	}
}