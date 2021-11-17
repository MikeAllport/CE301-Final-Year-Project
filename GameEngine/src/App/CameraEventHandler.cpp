#include "gepch.h"
#include "CameraEventHandler.h"
#include "Game.h"
#include "InputHandler.h"

// Code adapted from
// Y. Chernikov, Hazel Engine. 2021. [Online]. Available: https://github.com/TheCherno/Hazel [Accessed: 15-Apr- 2021]

namespace App
{
	CameraEventHandler::CameraEventHandler(std::shared_ptr<GE::Camera> camera)
		: camera(camera)
	{
		InputHandler::getInstance();
	}

	Camera2DHandler::Camera2DHandler(std::shared_ptr<GE::Camera> camera) :
		CameraEventHandler(camera)
	{

	}

	void CameraEventHandler::setZoom(float in)
	{
		this->zoomLevel = in;
		camera->setZoom(in);
	}

	void CameraEventHandler::setCameraPosition(glm::vec3 in)
	{
		this->cameraPosition = in;
		camera->setPosition(in);
	}

	void CameraEventHandler::setCamera(std::shared_ptr<GE::Camera> camera)
	{
		this->camera = camera;
	}

	void Camera2DHandler::onKeyEvent(GE::Event& e)
	{
		GE::KeyEvent* key = (GE::KeyEvent*) &e;
		delete key;
	}

	void Camera2DHandler::onUpdate(const float& dt)
	{
		bool pressed = false;
		if (InputHandler::getInstance()->isKeyPressed(KeyBindings::CAMERA_MOVE_UP))
		{
			cameraPosition.y += translationSpeed * Game::timePassedMS();
			pressed = true;
		}
		if (InputHandler::getInstance()->isKeyPressed(KeyBindings::CAMERA_MOVE_DOWN))
		{
			cameraPosition.y -= translationSpeed * Game::timePassedMS();
			pressed = true;
		}
		if (InputHandler::getInstance()->isKeyPressed(KeyBindings::CAMERA_MOVE_LEFT))
		{
			cameraPosition.x += translationSpeed * Game::timePassedMS();
			pressed = true;
		}
		if (InputHandler::getInstance()->isKeyPressed(KeyBindings::CAMERA_MOVE_RIGHT))
		{
			cameraPosition.x -= translationSpeed * Game::timePassedMS();
			pressed = true;
		}
		if (pressed)
			camera->setPosition(cameraPosition);
		//translationSpeed = zoomLevel;
	}

	void Camera2DHandler::onMouseEvent(GE::Event& e)
	{
		if (e.getType() == GE::EventType::MouseScrolled)
		{
			GE::MouseScrolledEvent* key = (GE::MouseScrolledEvent*) & e;
			zoomLevel += key->getOffsetY() * 0.25f;
			if (zoomLevel < 0.5f)
				zoomLevel = 0.5f;
			if (zoomLevel > 2.75f)
				zoomLevel = 2.75f;
			camera->setZoom(zoomLevel);
		}
	}

	Camera3DHandler::Camera3DHandler(std::shared_ptr<GE::Camera> camera, GameObject& character) :
		CameraEventHandler(camera), character(character)
	{
		cameraPosition = glm::vec3(character.getPosition().x, character.getPosition().y, character.getPosition().z);
	}

	void Camera3DHandler::onUpdate(const float& dt)
	{
		bool pressed = false;
		if (InputHandler::getInstance()->isKeyPressed(KeyBindings::CAMERA_MOVE_UP))
		{
			cameraPosition.z += translationSpeed * Game::timePassedMS();
			pressed = true;
		}
		if (InputHandler::getInstance()->isKeyPressed(KeyBindings::CAMERA_MOVE_DOWN))
		{
			cameraPosition.z -= translationSpeed * Game::timePassedMS();
			pressed = true;
		}
		if (InputHandler::getInstance()->isKeyPressed(KeyBindings::CAMERA_MOVE_RIGHT))
		{
			cameraPosition.x += translationSpeed * Game::timePassedMS();
			pressed = true;
		}
		if (InputHandler::getInstance()->isKeyPressed(KeyBindings::CAMERA_MOVE_LEFT))
		{
			cameraPosition.x -= translationSpeed * Game::timePassedMS();
			pressed = true;
		}
		Vector2D charposition(character.getPosition().x, character.getPosition().z);
		glm::vec3 charPos = character.getPosition();
		glm::vec3 cameraOffset = glm::vec3(0, character.size.y / 2, 0);
		glm::vec3 desiredPosition = charPos + cameraOffset;
		float desiredSpeed = 1 - std::pow(0.0125, dt);//std::min(0.5f, 10 * dt);
		cameraPosition = cameraPosition * (1.f - desiredSpeed) + desiredPosition * desiredSpeed;
		camera->setPosition(cameraPosition);
		translationSpeed = zoomLevel;
	}


	void Camera3DHandler::onMouseEvent(GE::Event& e)
	{
		if (e.getType() == GE::EventType::MouseScrolled)
		{
			GE::MouseScrolledEvent* key = (GE::MouseScrolledEvent*) & e;
			zoomLevel -= key->getOffsetY() * 0.25f;
			if (zoomLevel < 1.f)
				zoomLevel = 1.f;
			if (zoomLevel > 75.0f)
				zoomLevel = 75.0f;
			camera->setZoom(zoomLevel);
		}
	}
}