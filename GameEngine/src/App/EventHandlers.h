#ifndef APP_EVENTHANDLERS
#define APP_EVENTHANDLERS
#include "GE/Events/EventHandler.h"
namespace App
{
	class KeyEventHandler
	{
		virtual void onKeyEvent(GE::Event& e) = 0;
	};

	class MouseHandler
	{
		virtual void onMouseEvent(GE::Event& e) = 0;
	};
}
#endif // !APP_EVENTHANDLERS
