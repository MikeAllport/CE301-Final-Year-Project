#ifndef GE_KEYRELEV
#define GE_KEYRELEV

#include "gepch.h"
#include "GE/Events/Keys/KeyEvent.h"

namespace GE
{
	class KeyReleasedEvent :
		public KeyEvent
	{
	public:
		KeyReleasedEvent(const int keyCode);
		std::string toString() const override;
	};
}
#endif // !GE_KEYPRESSEV

