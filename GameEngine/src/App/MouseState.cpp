#include <gepch.h>
#include "MouseState.h"
#include <GE/Window.h>

namespace App
{
	Vector2D* MouseState::objectPosition = nullptr;
	void MouseState::setObjectUnderMouse(CommonGameObject* obj)
	{
		if (obj != nullptr)
		{
			Vector2D position = getPosition();
			if (objectPosition == nullptr)
				delete MouseState::objectPosition;
			MouseState::objectPosition = new Vector2D(position.x, position.y);
		}
		else if (objectPosition == nullptr)
		{
			delete MouseState::objectPosition;
		}
		objectUnderMouse = obj;
	}

	bool MouseState::isPositionObject(Vector2D position)
	{
		if (MouseState::objectPosition == nullptr)
			return false;
		return position == *MouseState::objectPosition;
	}

	Vector2D MouseState::getPosition()
	{
		auto pos = GE::MousePosition::getPosition();
		return Vector2D(pos.x, pos.y);
	}

	glm::vec3 MouseState::getScreenToWorldPosition(GE::Window& window)
	{
		Vector2D position = getPosition();
		return getScreenToWorldPosition(window, position);
	}

	glm::vec3 MouseState::getScreenToWorldPosition(GE::Window& window, Vector2D position)
	{
		glm::vec3 newPos;
		if (window.getActiveCameraType() == GE::CamType::PERSPECTIVE)
		{
			newPos = getScreenToWorldPerspective(window, position);
		}
		else
		{
			newPos = glm::vec3(1);
		}
		return newPos;
	}

	// Code adapted from
	// https://antongerdelan.net/opengl/raycasting.html
	glm::vec3 MouseState::getScreenToWorldPerspective(GE::Window& window, Vector2D position)
	{
		position = positionToNormalizedDevice(window, position);
		glm::vec3 ray = getRay(*window.getCamera(), position);
		glm::vec3 intersection(0);
		glm::vec3 rayOrigin = window.getCamera()->getCameraPosition();
		glm::vec3 pointOnSurface(100, 0, 100);
		if (rayIntersects(ray, rayOrigin, glm::vec3(0, 1, 0), pointOnSurface, intersection))
			return intersection;
		else
			return glm::vec3(NAN);
	}

	glm::vec3 MouseState::getRay(GE::Camera& cam, Vector2D position)
	{
		glm::vec4 homogenousCoords(position.x, position.y, 0, 1);
		glm::vec4 rayView = glm::inverse(cam.getProjection()) * homogenousCoords;
		rayView.z = -1;
		rayView.w = 0;
		glm::vec4 rayWorld = glm::inverse(cam.getView()) * rayView;
		return glm::normalize(rayWorld);
	}

	// Code adapted from
	// https://stackoverflow.com/questions/7168484/3d-line-segment-and-plane-intersection
	bool MouseState::rayIntersects(glm::vec3 ray, glm::vec3 rayOrigin, glm::vec3 norm, glm::vec3 point, glm::vec3& output)
	{
		float plane = glm::dot(norm, point);
		float d = glm::dot(norm, ray);
		if (!glm::dot(norm, ray))
			return false;
		float distanceToPlane = (plane - glm::dot(norm, rayOrigin)) / glm::dot(norm, ray);
		output = rayOrigin + distanceToPlane * ray;
		return true;
	}

	Vector2D MouseState::positionToNormalizedDevice(GE::Window& window, Vector2D position)
	{
		Vector2D result;
		result.x = (2.0f * position.x) / window.getWidth() - 1.0f;
		result.y = 1.0f - (2.0f * position.y) / window.getHeight();
		return result;
	}
}