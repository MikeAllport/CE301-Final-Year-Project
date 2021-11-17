#ifndef GE_MOUSESTATE
#define GE_MOUSESTATE

#include "gepch.h"
#include "GLFW/glfw3.h"

/**
* MouseState is a singleston class which holds the current position of the mouse
* with setters and getters
*/
namespace GE
{
	class MousePosition
	{
	public:
		static MousePosition& getState()
		{
			static MousePosition mouse;
			return mouse;
		};

		static glm::ivec2 getPosition()
		{
			MousePosition& mouse = getState();
			if (!MousePosition::initialized)
				throw "GE MousePosition not initialized";
			glfwGetCursorPos(mouse.window, &mouse.mousex, &mouse.mousey);
			return glm::ivec2(std::round(mouse.mousex), std::round(mouse.mousey));
		}
	private:
		friend class Window;
		friend class BaseApp;
		inline static void SetMouse(GLFWwindow* window) { 
			MousePosition& mouse = getState();
			mouse.window = window;
			MousePosition::initialized = true;
		}
		MousePosition() : mousex(0), mousey(0) {};
		double mousex, mousey;
		GLFWwindow* window;
		static bool initialized;
	};
}
#endif // !GE_MOUSESTATE
