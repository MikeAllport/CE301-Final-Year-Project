#include "gepch.h"
#include "Camera.h"

namespace GE
{
	Camera::Camera(Window& window, glm::mat4 projection, glm::vec3 position, float zoom) :
		window(window), projection(projection), position(position), zoom(zoom),
		view(glm::mat4(1.0f)), viewProjection(glm::mat4(1.0f))
	{
	}

	glm::mat4 Camera::getProjection()
	{
		return projection;
	}

	glm::mat4 Camera::getView()
	{
		return view;
	}

	glm::vec3 Camera::getPosition()
	{
		return position;
	}

	glm::vec3 Camera::getCameraPosition()
	{
		return cameraPosition;
	}

	glm::mat4 Camera::getViewProjection()
	{
		refresh();
		return viewProjection;
	}

	float* Camera::getZoom()
	{
		return &zoom;
	}

	void Camera::setOffset(glm::vec3& offset)
	{
		positionOffset = &offset;
	}

	void Camera::removeOffset()
	{
		positionOffset = nullptr;
	}

	Camera2D::Camera2D(Window& window) :
		Camera(window, glm::ortho(0.0f, (float)window.getWidth(), (float)window.getHeight(), 0.0f, -1.0f, 1.0f))
	{
		refresh();
	}

	void Camera2D::setPosition(const glm::vec3 position)
	{
		this->position = position;
		refresh();
	}

	void Camera2D::setZoom(const float in)
	{
		zoom = in;
		refresh();
	}

	void Camera2D::refresh()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
		view = glm::inverse(transform);
		glm::mat4 newProj = glm::mat4(projection);
		newProj = glm::translate(newProj, glm::vec3((float)window.getWidth() / 2.0f, (float)window.getHeight() / 2.0f, 1.0f));
		newProj = glm::scale(newProj, glm::vec3(zoom, zoom, 0.0f));
		newProj = glm::translate(newProj, glm::vec3(-(float)window.getWidth() / 2.0f, -(float)window.getHeight() / 2.0f, 1.0f));
		viewProjection = newProj * view;
	}

	void Camera2D::onWindowResize()
	{
		projection = glm::ortho(0.0f, (float)window.getWidth(), (float)window.getHeight(), 0.0f, -1.0f, 1.0f);
		glViewport(0, 0, window.getWidth(), window.getHeight());
		refresh();
	}

	PerspectiveCamera::PerspectiveCamera(Window& window) :
	Camera(window, glm::perspective(glm::radians(45.0f * zoom), (float)window.getWidth() / (float)window.getHeight(), znear, zfar * zoom))
	{
		refresh();
	}

	void PerspectiveCamera::setPosition(const glm::vec3 position)
	{
		this->position = position;
		refresh();
	}

	void PerspectiveCamera::setZoom(const float in)
	{
		zoom = in;
		refresh();
	}

	void PerspectiveCamera::refresh()
	{
		resetProjection();
		glm::vec3 newPosition = (positionOffset != nullptr) ? this->position + *this->positionOffset : this->position;
		cameraPosition = glm::vec3(newPosition.x, camDistance * zoom, newPosition.z + camDistance * zoom);
		view = glm::lookAt(cameraPosition, newPosition, glm::vec3(0.0f, 1.0f, 0.0f));
		viewProjection = projection * view;
	}
	void PerspectiveCamera::resetProjection()
	{
		if (window.isActive())
			projection = glm::perspective(glm::radians(45.0f), (float)window.getWidth() / (float)window.getHeight(), znear, zfar * zoom);
	}

	void PerspectiveCamera::onWindowResize()
	{
		resetProjection();
		window.onResize();
		glViewport(0, 0, window.getWidth(), window.getHeight());
		refresh();
	}
}