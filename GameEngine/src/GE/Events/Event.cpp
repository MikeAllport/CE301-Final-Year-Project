#include "gepch.h"
#include "Event.h"

namespace GE
{
	EventType Event::getType() const
	{
		return type;
	}
	EventCategory Event::getCategory() const
	{
		return category;
	}
	Event::Event(const EventType& type, const EventCategory& cat)
		: type(type), category(cat)
	{
	}
}