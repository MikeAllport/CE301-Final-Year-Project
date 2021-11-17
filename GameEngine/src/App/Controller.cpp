#include "gepch.h"
#include "Controller.h"
#include "Game.h"
#include "InputHandler.h"

namespace App
{
	Controller::Controller() :
		_action()
	{
	}

	Action Controller::GetAction()
	{
		return _action;
	}

	void Controller::onUpdate()
	{
		bool depthPressed = false, horizontalPressed = false;;
		if (InputHandler::getInstance()->isKeyPressed(KeyBindings::CHARACTER_MOVE_DOWN))
		{
			_action.CharacterDepthMovement += (_action.CharacterDepthMovement < 1) ? 1 : 0;
			depthPressed = true;
		}
		if (InputHandler::getInstance()->isKeyPressed(KeyBindings::CHARACTER_MOVE_UP))
		{
			_action.CharacterDepthMovement += (_action.CharacterDepthMovement > -1) ? -1 : 0;
			depthPressed = true;
		}
		if (InputHandler::getInstance()->isKeyPressed(KeyBindings::CHARACTER_MOVE_RIGHT))
		{
			_action.CharacterHorizontalMovement += (_action.CharacterHorizontalMovement < 1) ? 1 : 0;
			horizontalPressed = true;
		}
		if (InputHandler::getInstance()->isKeyPressed(KeyBindings::CHARACTER_MOVE_LEFT))
		{
			_action.CharacterHorizontalMovement += (_action.CharacterHorizontalMovement > -1) ? -1 : 0;
			horizontalPressed = true;
		}
		if (!depthPressed)
			_action.CharacterDepthMovement = 0;
		if (!horizontalPressed)
			_action.CharacterHorizontalMovement = 0;
		moved = depthPressed || horizontalPressed;
	}
}
