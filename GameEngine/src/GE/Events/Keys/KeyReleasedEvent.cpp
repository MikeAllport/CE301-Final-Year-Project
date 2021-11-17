#include "gepch.h"
#include "KeyReleasedEvent.h"

namespace GE
{
	KeyReleasedEvent::KeyReleasedEvent(const int keyCode)
		: KeyEvent(keyCode, EventType::KeyPressed)
	{
	}

	std::string KeyReleasedEvent::toString() const
	{
		return "KeyReleasedEvent: key = " + keyName;
	}
}