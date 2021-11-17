#include "gepch.h"
#include "KeyPressedEvent.h"

namespace GE
{
	KeyPressedEvent::KeyPressedEvent(const int keyCode)
		: KeyEvent(keyCode, EventType::KeyPressed)
	{
	}

	std::string KeyPressedEvent::toString() const
	{
		return "KeyPressedEvent: key = " + keyName;
	}
}