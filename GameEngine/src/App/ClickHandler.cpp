#include "gepch.h"
#include "ClickHandler.h"
#include "CharacterObject.h"

namespace App
{
	ClickHandler::ClickHandler(GE::Window& window, CharacterObject& character):
		window(window),
		character(character)
	{
	}
	void ClickHandler::onMouseEvent(GE::Event& e)
	{
		if (e.getType() == GE::EventType::MouseButPressed)
		{
			GE::MouseClickedEvent* key = (GE::MouseClickedEvent*)(&e);
			if (key != nullptr)
			{
				sendClick(key->keyPressed());
			}
		}
	}

	void ClickHandler::sendClick(GE::MouseButton but)
	{
		Vector2D mousePos = MouseState::getPosition();
		if (window.isPointInWindow(mousePos.x, mousePos.y))
		{
			switch (but)
			{
			case GE::MouseButton::Button_1:
				if (MouseState::isPositionObject(mousePos))
				{
					character.moveToObject(MouseState::objectUnderMouse);
				}
				else
				{
					glm::vec3 worldPos = MouseState::getScreenToWorldPosition(window, mousePos);
					character.moveToFloor(worldPos.x, worldPos.z);
				}
				break;
			case GE::MouseButton::Button_2:
				break;
			}
		}
	}
}
