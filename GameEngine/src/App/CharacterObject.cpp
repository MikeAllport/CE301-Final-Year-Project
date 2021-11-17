#include <gepch.h>
#include "CharacterObject.h"

namespace App
{
	CharacterObject::CharacterObject(glm::fvec3 position, Controller& controller) :
		CommonGameObject(position, CHARACTER),
		controller(controller),
		objectPos(-1, -1)
	{
	}

	void CharacterObject::onUpdate(const float& DT)
	{
		if (isValidObjectPos() && !controller.moved)
			moveToObject();
		else
			moveToController();
		
		GameObject::onUpdate(DT);
	}

	void CharacterObject::moveToObject()
	{
		if (movingToObject)
		{
			if (objectPos.Distance(Vector2D(position.x, position.z)) <= size.x / 2)
			{
				clearObjectPos();
				return;
			}
		}
		else
		{
			if (objectPos.Distance(Vector2D(position.x, position.z)) <= 8)
			{
				clearObjectPos();
				return;
			}
		}
		Vector2D direction = objectPos - Vector2D(position.x, position.z);
		velocity = direction.Normalize() * MAX_SPEED;
	}

	void CharacterObject::moveToObject(CommonGameObject* obj)
	{
		if (!obj)
			return;
		movingToObject = true;
		setMoveTo(obj->getPosition().x, obj->getPosition().z);
	}

	void CharacterObject::moveToFloor(int x, int y)
	{
		movingToObject = false;
		setMoveTo(x, y);
	}

	void CharacterObject::moveToController()
	{
		clearObjectPos();
		Action action = controller.GetAction();
		velocity = Vector2D(action.CharacterHorizontalMovement, action.CharacterDepthMovement).Normalize() * MAX_SPEED;
	}


	void CharacterObject::setMoveTo(int x, int y)
	{
		objectPos = Vector2D(x, y);
	}

	void CharacterObject::clearObjectPos()
	{
		movingToObject = false;
		objectPos = Vector2D(-1, -1);
	}

	bool CharacterObject::isValidObjectPos()
	{
		return objectPos.x != -1 || objectPos.y != -1;
	}
}