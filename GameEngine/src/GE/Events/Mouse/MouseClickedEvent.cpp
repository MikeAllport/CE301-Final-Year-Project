#include "gepch.h"
#include "MouseClickedEvent.h"

namespace GE
{
	MouseClickedEvent::MouseClickedEvent(int code) :
		MouseEvent(code)
	{}

	std::string MouseClickedEvent::toString() const
	{
		return "MouseClickedEvent: button= " + toStringBut(keyPressed());
	}
}