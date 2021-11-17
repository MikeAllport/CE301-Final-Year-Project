#ifndef GE_MOUSESCROLLEV
#define GE_MOUSESCROLLEV

#include "GE/Events/Event.h"

namespace GE
{
	class MouseScrolledEvent: public Event
	{
	public:
		MouseScrolledEvent(const double offsetX, const double offsetY);
		double getOffsetX();
		double getOffsetY();
		std::string toString() const override;
	private:
		double offsetX, offsetY;
	};
}
#endif // !GE_MOUSESCROLLEV
