#include "gepch.h"
#include "EventHandler.h"

namespace GE
{

	void EventHandler::addEventCategory(const EventCategory& cat)
	{
		EventTrasmitter::getHandler().attachEventListener(*this, cat);
		GE_INFO("Attaching event listener {0} to {1}", toString(EventCategory(cat)), typeid(*this).name());
	}

	EventHandler::~EventHandler()
	{
		EventTrasmitter::getHandler().removeEventListener(*this);
	}

	EventTrasmitter::~EventTrasmitter()
	{
		if (applicationListeners.size() != 0)
			applicationListeners.clear();
		if (mouseListeners.size() != 0)
			mouseListeners.clear();
		if (keyboardListeners.size() != 0)
			keyboardListeners.clear();
	}

	// EventHandler implementation
	EventTrasmitter& EventTrasmitter::getHandler()
	{
		static EventTrasmitter h;
		return h;
	}

	bool EventTrasmitter::attachEventListener(EventHandler& listener, const EventCategory& cat)
	{
		bool attached = false;
		if (cat == EventCategory::Application)
		{
			applicationListeners.push_back(&listener);
			attached = true;
		}
		if (cat == EventCategory::Keyboard)
		{
			keyboardListeners.push_back(&listener);
			attached = true;
		}
		if (cat == EventCategory::Mouse)
		{
			mouseListeners.push_back(&listener);
			attached = true;
		}
		return attached;
	}

	bool EventTrasmitter::removeEventListener(EventHandler& listener)
	{
		bool removed = false;
		const EventHandler* list = &listener;
		for (auto it = applicationListeners.begin(); it != applicationListeners.end();)
		{
			if (list == *it)
			{
				it = applicationListeners.erase(it);
				removed = true;
			}
			else it++;
		}
		for (auto it = keyboardListeners.begin(); it != keyboardListeners.end();)
		{
			if (list == *it)
			{
				it = keyboardListeners.erase(it);
				removed = true;
			}
			else it++;
		}
		for (auto it = mouseListeners.begin(); it != mouseListeners.end();)
		{
			if (list == *it)
			{
				it = mouseListeners.erase(it);
				removed = true;
			}
			else it++;
		}
		return removed;
	}

	bool EventTrasmitter::dispatch(Event& e)
	{
		EventTrasmitter& eh = getHandler();
		switch (e.getCategory())
		{
		case EventCategory::Application:
			return eh.dispatchApplicationEvent(e);
			break;
		case EventCategory::Keyboard:
			return eh.dispatchKeyboardEvent(e);
			break;
		case EventCategory::Mouse:
			return eh.dispatchMouseEvent(e);
			break;
		}
		return false;
	}

	bool EventTrasmitter::dispatchApplicationEvent(Event& e)
	{
		bool dispatched = false;
		for (auto it = applicationListeners.begin(); it != applicationListeners.end(); it++)
		{
			(*it)->onEvent(e);
			dispatched = true;
		}
		return dispatched;
	}

	bool EventTrasmitter::dispatchKeyboardEvent(Event& e)
	{
		bool dispatched = false;
		for (auto it = keyboardListeners.begin(); it != keyboardListeners.end(); it++)
		{
			(*it)->onEvent(e);
			dispatched = true;
		}
		return dispatched;
	}
	bool EventTrasmitter::dispatchMouseEvent(Event& e)
	{
		bool dispatched = false;
		for (auto it = mouseListeners.begin(); it != mouseListeners.end(); it++)
		{
			if (*it)
			{
				(*it)->onEvent(e);
				dispatched = true;
			}
		}
		return dispatched;
	}
}