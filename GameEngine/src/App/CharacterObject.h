#ifndef APP_CHARACTEROBJ
#define APP_CHARACTER_OBJ

#include "GameObject.h"
#include "Controller.h"
#include "Sprite.h"

namespace App
{
	class CharacterObject : public CommonGameObject
	{
	public:
		CharacterObject(glm::fvec3 position, Controller& controller);
		void onUpdate(const float& DT) override;
		inline static const int MAX_SPEED = 250, MAX_ACC = 600, DRAG = 5;
		void moveToObject(CommonGameObject* obj);
		void moveToFloor(int x, int y);
		Vector2D objectPos;
	private:
		void setMoveTo(int x, int y);
		void moveToController();
		void moveToObject();
		bool movingToObject = false;
		bool isValidObjectPos();
		void clearObjectPos();
		Controller& controller;
	};
}
#endif