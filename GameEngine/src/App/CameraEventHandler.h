#ifndef GE_CAMERACONTROLLER
#define GE_CAMERACONTROLLER

#include "EventHandlers.h"
#include "GE/Camera.h"
#include "Vector2D.h"
#include "GameObject.h"

namespace App
{
	class CameraEventHandler: public KeyEventHandler, public MouseHandler
	{
	public:
		CameraEventHandler(std::shared_ptr<GE::Camera> camera);
		~CameraEventHandler() {};
		virtual void onKeyEvent(GE::Event& e) override = 0;
		virtual void onMouseEvent(GE::Event& e) override = 0;
		virtual void onUpdate(const float& dt) = 0;
		void setCamera(std::shared_ptr<GE::Camera> cam);
		void setZoom(float in);
		void setCameraPosition(glm::vec3 in);
	protected:
		std::shared_ptr<GE::Camera> camera;
		float translationSpeed = 1.0f, zoomLevel = 1.0f; // 1 pixel per millisecond
		glm::fvec3 cameraPosition = glm::vec3(0.0f);
	};

	class Camera2DHandler : public CameraEventHandler
	{
	public:
		Camera2DHandler(std::shared_ptr<GE::Camera> camera);
		void onKeyEvent(GE::Event& e) override;
		void onMouseEvent(GE::Event& e) override;
		void onUpdate(const float& dt) override;
	};

	class Camera3DHandler : public CameraEventHandler
	{
	public:
		Camera3DHandler(std::shared_ptr<GE::Camera> camera, GameObject& character);
		void onKeyEvent(GE::Event& e) override {};
		void onMouseEvent(GE::Event& e) override;
		void onUpdate(const float& dt) override;
	private:
		friend class Game;
		Vector2D currentVelocity;
		GameObject& character;
	};
}
#endif // !GE_CAMERACONTROLLER
