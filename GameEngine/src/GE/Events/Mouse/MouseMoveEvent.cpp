#include "gepch.h"
#include "MouseMoveEvent.h"

namespace GE
{
	MouseMoveEvent::MouseMoveEvent(double xpos, double ypos):
		Event(EventType::MouseMoved, EventCategory::Mouse),
		posx(xpos), posy(ypos)
	{
	}
	double MouseMoveEvent::getX() const
	{
		return posx;
	}
	double MouseMoveEvent::getY() const
	{
		return posy;
	}
	std::string MouseMoveEvent::toString() const
	{
		return "MouseMovedEvent: posx = " + STRINGY(posx) + ", posy = " +
			STRINGY(posy);
	}
}