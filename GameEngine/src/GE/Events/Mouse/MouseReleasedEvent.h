#ifndef GE_MOUSERELEV
#define GE_MOUSERELEV

#include "MouseEvent.h"

namespace GE
{
	class MouseReleasedEvent : public MouseEvent
	{
	public:
		MouseReleasedEvent(int code);
		std::string toString() const override;
	};
}
#endif // !GE_MOUSECLICKEV
