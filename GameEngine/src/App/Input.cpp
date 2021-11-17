#include "gepch.h"
#include "InputHandler.h"

namespace App
{

	GLFWwindow* InputHandler::window = nullptr;
	InputHandler* InputHandler::getInstance()
	{
		static InputHandler* h = new InputHandler();
		window = GE::BaseApp::getApp().getWindow().getGLFWWindow();
		return h;
	}

	bool InputHandler::isKeyPressed(int key)
	{
		auto type = glfwGetKey(window, key);
		return type == GLFW_PRESS || type == GLFW_REPEAT;
	}
}