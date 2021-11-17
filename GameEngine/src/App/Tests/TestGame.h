#ifndef APP_TESTGAME
#define APP_TESTGAME

#include <App/Game.h>

#include <GE/Graphics/FontRenderer.h>
// Tests
#include "Tests.h"

// opengl stuffs
#include <Glad/glad.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
namespace App
{
	/**
	* TestGame's purpose is to run controlled tests in an ImGui environment such that
	* initialize tests class
	* push tests
	* run loop ->
	*	update tests
	*	update window
	*/
	class TestGame : public Game
	{
	public:
		TestGame();
		~TestGame();
		void run() override;
		void initImGui();
		void destroyImGui();
	};
}
#endif // !APP_TESTGAME
