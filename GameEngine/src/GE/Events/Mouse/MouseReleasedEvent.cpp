#include "gepch.h"
#include "MouseReleasedEvent.h"

namespace GE
{
	MouseReleasedEvent::MouseReleasedEvent(int code) :
		MouseEvent(code)
	{}

	std::string MouseReleasedEvent::toString() const
	{
		return "MouseClickedReleased: button= " + toStringBut(keyPressed());
	}
}