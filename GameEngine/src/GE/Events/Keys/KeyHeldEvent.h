#ifndef GE_KEYHELVEV
#define GE_KEYHELVEV

#include "gepch.h"
#include "GE/Events/Keys/KeyEvent.h"

namespace GE
{
	class KeyHeldEvent :
		public KeyEvent
	{
	public:
		KeyHeldEvent(const int keyCode);
		std::string toString() const override;
	};
}
#endif // !GE_KEYHELVEV

