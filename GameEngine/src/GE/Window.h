#ifndef GE_WINDOW
#define GE_WINDOW


#include "glad/glad.h"
#include "Events/EventHandler.h"
#include "Events/Window/WindowClosedEvent.h"
#include "Events/Window/WindowResizedEvent.h"
#include "Events/Keys/KeyPressedEvent.h"
#include "Events/Keys/KeyHeldEvent.h"
#include "Events/Keys/KeyReleasedEvent.h"
#include "Events/Mouse/MouseClickedEvent.h"
#include "Events/Mouse/MouseMoveEvent.h"
#include "Events/Mouse/MouseReleasedEvent.h"
#include "Events/Mouse/MouseScrolledEvent.h"
#include "GLFW/glfw3.h"

namespace GE
{
	class Camera;

	enum CamType
	{
		PERSPECTIVE, ORTHO
	};

	/**
	* WindowProps is a data class for standard window properties
	*/
	struct WindowProps
	{
		std::string title = "GameEngine Window";
		int width = 1200, height = 780;
		bool VSync = true;
		WindowProps() {};
		WindowProps(const std::string& title, uint32 width, uint32 height);
		WindowProps(const WindowProps& other);
		~WindowProps() = default;
	};

	/**
	* Window class acts as a window and opengl context via the GLFW dependancy
	*/
	class Window 
	{
	public:
		Window(const WindowProps& props = WindowProps());
		~Window();
		// update method per tick
		bool isPointInWindow(int x, int y);
		// properties getters
		uint32 getWidth() const;
		uint32 getHeight() const;

		GLFWwindow* getGLFWWindow() {
			return window;
		};
		std::shared_ptr<GE::Camera> getCamera();
		void setCamera(CamType type);
		void useMainWindow();
		void useHiddenWindow();
		void useHandCursor();
		void useNormalCursor();
		bool isActive();
		CamType& getActiveCameraType() { return activeCamType; };
		static inline const glm::vec3 WINDOW_COLOR = glm::vec3(51, 76, 76);
		static inline GLFWwindow* window,* hiddenWindow;
		void onResize();
		void onUpdate();

	private:
		friend class Camera;
		friend class PerspectiveCamera;
		friend class Camera2D;
		friend class BaseApp;
		void setActive(bool is);
		void onReset();
		void onShutdown();
		void initWindow(int id);
		void useWindow(GLFWwindow* window);
		void initGlad();
		void initCallbacks();
		void setProps();
		void initGLFW();

		static void GLAPIENTRY glErrorCallback(
			GLenum source,
			GLenum type,
			GLuint id,
			GLenum severity,
			GLsizei length,
			const GLchar* message,
			const void* userParam);
		static const char* glGetErrorFlags(GLenum& arg);

		std::shared_ptr<GE::Camera> activeCamera;
		std::shared_ptr<GE::Camera> perspectiveCamera;
		std::shared_ptr<GE::Camera> orthoCamera;
		CamType activeCamType = ORTHO;
		WindowProps props;
		bool GLFWInitialized = false;
		bool active = true;
	};
}
#endif // !GE_WINDOW


