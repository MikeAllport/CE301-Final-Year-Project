#ifndef GE_EVENTHANDLER
#define GE_EVENTHANDLER

#include "Event.h"

namespace GE
{
	// pure abstract class / interface to be realised by event handling classes
	class EventHandler
	{
	public:
		virtual void onEvent(Event& e) = 0;
	protected:
		//EventHandler();
		~EventHandler();
		void addEventCategory(const EventCategory& cat);
	};

	/**
	* Event handler class is a singleton instance which handles the dispatching of events, and
	* keeping track of classes which implement EventListener to dispatch events too
	*/
	class EventTrasmitter
	{
	public:
		~EventTrasmitter();
		static bool dispatch(Event& e);
		bool attachEventListener(EventHandler& listener, const EventCategory& cat);
		bool removeEventListener(EventHandler& listener);
	private:
		friend class EventHandler;
		static EventTrasmitter& getHandler();
		EventTrasmitter() : applicationListeners(), keyboardListeners(), mouseListeners()
		{}
		std::list<EventHandler*> applicationListeners;
		std::list<EventHandler*> keyboardListeners;
		std::list<EventHandler*> mouseListeners;
		bool dispatchApplicationEvent(Event& e);
		bool dispatchKeyboardEvent(Event& e);
		bool dispatchMouseEvent(Event& e);
	};
}
#endif // !GE_EVENTHANDLER
