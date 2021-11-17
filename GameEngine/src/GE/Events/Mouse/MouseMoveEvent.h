#ifndef GE_MOUSEMOVEEV
#define GE_MOUSEMOVEEV

#include "GE/Events/Event.h"

namespace GE
{
	class MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(double xpos, double ypos);
		double getX() const;
		double getY() const;
		std::string toString() const override;
	private:
		double posx, posy;
	};
}
#endif // !GE_MOUSEMOVEEV
