#include "gepch.h"
#include "TestGame.h"
#include <imgui/imgui_internal.h>

namespace App
{
	void MyFunction(int& x)
	{
	}
	TestGame::TestGame() : Game() 
	{
	};

	TestGame::~TestGame()
	{
		destroyImGui();
	}

	void TestGame::run()
	{
		initImGui();
		std::shared_ptr<TESTS::Test> currentTest;
		std::shared_ptr<TESTS::Menu> testMenu(new TESTS::Menu(currentTest, *this));
		currentTest = testMenu;
		//testMenu->pushTest<TESTS::WorldTileTest>("World Generation test v1", *this);
		// main loop 
		while (isRunning)
		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			if (currentTest)
			{
				ImGui::Begin(currentTest->name.c_str());
				// resets to base menu imgui window
				if (currentTest != testMenu && ImGui::Button("<-"))
				{
					currentTest.reset();
					currentTest = testMenu;
				}
				currentTest->onImgui();
				currentTest->onUpdate(timePassedMS());
				currentTest->onRender();

				ImGui::End();
			}
			//ImGuiIO& io = ImGui::GetIO();
			//GE::Window* window = GE::BaseApp::getApp().getWindow();
			//io.DisplaySize = ImVec2((float)window->getWidth(), (float)window->getHeight());

			// Rendering
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			onUpdate();
		}
	}

	void TestGame::initImGui()
	{
		ImGui::CreateContext();

		ImGui::StyleColorsDark();
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(window->getGLFWWindow(), true);
	}

	void TestGame::destroyImGui()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
}