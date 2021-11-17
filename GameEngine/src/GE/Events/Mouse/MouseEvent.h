#ifndef GE_MOUSEEV
#define GE_MOUSEEV

#include "GE/Events/Event.h"

/**
* MouseEvent acts as an abstract class for mouse click events to inherit, adding what type
* of mouse buton has been clicked to the event
*/
namespace GE
{
	//TODO: Setup other buttons if implementing for wider range of audience
	enum class MouseButton
	{
		Button_1,
		Button_2,
		Invalid
	};

	inline std::string toStringBut(MouseButton but)
	{
		switch (but)
		{
		case MouseButton::Button_1:
			return "Button1";
		case MouseButton::Button_2:
			return "Button2";
		default:
			return "Invalid";
		}
	}

	class MouseEvent : public Event
	{
	public:
		MouseButton keyPressed() const { return key; };
		virtual std::string toString() const override = 0;
	protected:
		MouseEvent(const int code):
			Event(EventType::MouseButPressed, EventCategory::Mouse)
		{
			switch (code)
			{
			case 0:
				key = MouseButton::Button_1;
				break;
			case 1:
				key = MouseButton::Button_2;
				break;
			default:
				key = MouseButton::Invalid;
			}
		};
	private:
		MouseButton key;
	};
}
#endif // !GE_MOUSEEV
