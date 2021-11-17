#ifndef GAME_IDRAW
#define GAME_IDRAW

#include "GE/Graphics/Renderer.h"

namespace App
{
	class IDrawable
	{
	public:
		virtual void draw(GE::Graphics::Renderer& rc) = 0;
	};

	class IUpdateable
	{
	public:
		virtual void onUpdate() = 0;
	};

	class IUpdateableDT
	{
	public:
		virtual void onUpdate(const float& deltaT) = 0;
	};

	class IRenderable
	{
	public:
		virtual void onRender() = 0;
	};
}
#endif