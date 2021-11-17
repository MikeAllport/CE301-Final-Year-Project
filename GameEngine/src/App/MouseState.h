#pragma once
#include "Vector2D.h"
#include <glm.hpp>
#include <GE/MousePosition.h>
#include <GE/Window.h>
#include <GE/Camera.h>
#include <App/GameObject.h>
#include <GE/BaseApp.h>

namespace App
{
	class MouseState
	{
	public:
		static inline CommonGameObject* objectUnderMouse = nullptr;
		static void setObjectUnderMouse(CommonGameObject* obj);
		static Vector2D getPosition();
		static glm::vec3 getScreenToWorldPosition(GE::Window& window);
		static glm::vec3 getScreenToWorldPosition(GE::Window& window, Vector2D position);
		static bool isPositionObject(Vector2D position);
		static Vector2D* objectPosition;
	private:
		static glm::vec3 getRay(GE::Camera& cam, Vector2D position);
		static bool rayIntersects(glm::vec3 ray, glm::vec3 rayOrigin, glm::vec3 norm, glm::vec3 point, glm::vec3& output);
		static glm::vec3 getScreenToWorldPerspective(GE::Window& window, Vector2D position);
		static Vector2D positionToNormalizedDevice(GE::Window& window, Vector2D position);
	};
}