#ifndef GE_MOUSECLICKEV
#define GE_MOUSECLICKEV

#include "MouseEvent.h"

namespace GE
{
	class MouseClickedEvent : public MouseEvent
	{
	public:
		MouseClickedEvent(int code);
		std::string toString() const override;
	};
}
#endif // !GE_MOUSECLICKEV
