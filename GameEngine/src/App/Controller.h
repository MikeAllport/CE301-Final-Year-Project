#ifndef APP_CONTROLLER
#define APP_CONTROLLER

#include "Action.h"
#include "EventHandlers.h"
#include <GE/Events/Keys/KeyEvent.h>
#include <App/Interfaces.h>

namespace App
{
	class Controller: IUpdateable
	{
	public:
		Controller();
		Action GetAction();
		void onUpdate() override;
		bool moved;
	protected:
		Action _action;
	};
}
#endif