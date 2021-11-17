#ifndef GE_WINDWCLOSEDEV
#define GE_WINDOWCLOSEDEV

#include "gepch.h"
#include "GE/Events/Event.h"

namespace GE
{
	class WindowClosedEvent: public Event
	{
	public:
		WindowClosedEvent();
		std::string toString() const override;
	};
}
#endif // !GE_WINDWCLOSEDEV
