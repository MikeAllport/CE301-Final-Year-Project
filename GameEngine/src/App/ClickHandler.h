#ifndef APP_CLICK_HANDLER
#define APP_CLICK_HANDLER

#include "gepch.h"
#include "EventHandlers.h"
#include "MouseState.h"

namespace App
{
	extern class CharacterObject;
	class ClickHandler : public MouseHandler
	{
	public:
		ClickHandler(GE::Window& window, CharacterObject& character);
		void onMouseEvent(GE::Event& e) override;
	private:
		void sendClick(GE::MouseButton button);
		GE::Window& window;
		CharacterObject& character;
	};
}
#endif // !APP_CLICK_HANDLER