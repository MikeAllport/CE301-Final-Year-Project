#ifndef APP_INPUTHANDLER
#define APP_INPUTHANDLER

#include "gepch.h"
#include "Game.h"
#include "GLFW/glfw3.h"

namespace App
{
	class InputHandler
	{
	public:
		static InputHandler* getInstance();
		bool isKeyPressed(int key);
	private:
		static GLFWwindow* window;
	};
}
#endif