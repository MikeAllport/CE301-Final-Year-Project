#pragma once

#include <App/Interfaces.h>
#include <GE/Events/Event.h>

namespace App
{
	class ILayer: public IUpdateableDT
	{
	public:
		virtual void onRender() = 0;
		virtual void onUpdate(const float& delta) override = 0;
		virtual void onEvent(GE::Event& e) = 0;
		bool isDead = false;
	};
}
