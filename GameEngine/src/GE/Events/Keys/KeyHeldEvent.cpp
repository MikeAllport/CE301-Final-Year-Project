#include "gepch.h"
#include "KeyHeldEvent.h"

namespace GE
{
	KeyHeldEvent::KeyHeldEvent(const int keyCode)
		: KeyEvent(keyCode, EventType::KeyHeld)
	{
	}

	std::string KeyHeldEvent::toString() const
	{
		return "KeyHeldEvent: key = " + keyName;
	}
}