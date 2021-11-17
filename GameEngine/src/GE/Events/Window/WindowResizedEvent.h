#ifndef GE_WINDOWRESIZEEVENT
#define GE_WINDOWRESIZEEVENT

#include "gepch.h"
#include "GE/Events/Event.h"

/**
* WindowResizedEvent extends the event class and represents window resized
*/
namespace GE
{
	class WindowResizedEvent: public Event
	{
	public:
		WindowResizedEvent(const uint32 width, const uint32 height);
		std::string toString() const override;
		uint32 getWidth() const;
		uint32 getHeight() const;

	private:
		uint32 width, height;
	};
}
#endif // !GE_WINDOWRESIZEEVENT
