#ifndef GE_CAMERA
#define GE_CAMERA

#include "Window.h"

namespace GE
{
	/**
	* Camera class acts as a pure virtual interface declaring operations both the orthographics
	* and perspective camera must implement and realise
	*/
	class Camera
	{
	public:
		Camera(Window& window, glm::mat4 projection,
			glm::vec3 position = glm::vec3(0.0f), float zoom = 1.0f);
		virtual ~Camera() = default;
		virtual void setPosition(const glm::vec3 position) = 0;
		virtual void setZoom(const float in) = 0;
		glm::mat4 getViewProjection();
		virtual void onWindowResize() = 0;
		glm::mat4 getProjection();
		glm::mat4 getView();
		glm::vec3 getPosition();
		glm::vec3 getCameraPosition();
		void setOffset(glm::vec3& position);
		void removeOffset();
		float* getZoom();
		float zoom;
	protected:
		glm::vec3 cameraPosition;
		glm::vec3 position;
		virtual void refresh() = 0;
		Window& window;
		glm::mat4 projection;
		glm::mat4 view;
		glm::mat4 viewProjection;
		glm::vec3* positionOffset = nullptr;
	};

	/**
	* Camera's responsibility is to update the projection matrice used in translating
	* world coordinate system to screen coordinates (normalized device coordinates)
	* as an orthographic camera and to translate/scale dependant upon camera position
	* and zoom level
	*/
	class Camera2D : public Camera
	{
	public:
		Camera2D(Window& window);

		void setPosition(const glm::vec3 position) override;
		void setZoom(const float in) override;
		void onWindowResize() override;
	private:
		// updates the view, projection, and viewProjection matrices upon current
		// position, zoom, and window size
		void refresh() override;
	};

	/**
	* Camera's responsibility is to update the projection matrice used in translating
	* world coordinate system to screen coordinates (normalized device coordinates)
	* as an orthographic camera and to translate/scale dependant upon camera position
	* and zoom level
	*/
	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(Window& window);

		void setPosition(const glm::vec3 position) override;
		void setZoom(const float in) override;
		void onWindowResize() override;
		float znear = 0.1f, zfar = 1800.0f, camDistance = 600.0f;

	private:
		// updates the view, projection, and viewProjection matrices upon current
		// position, zoom, and window size
		void refresh() override;
		void resetProjection();

	};
}
#endif // !GE_CAMERA
