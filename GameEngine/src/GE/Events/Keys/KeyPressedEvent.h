#ifndef GE_KEYPRESSEV
#define GE_KEYPRESSEV

#include "gepch.h"
#include "GE/Events/Keys/KeyEvent.h"

namespace GE
{
	class KeyPressedEvent :
		public KeyEvent
	{
	public:
		KeyPressedEvent(const int keyCode);
		std::string toString() const override;
	};
}
#endif // !GE_KEYPRESSEV

