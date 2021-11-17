#include "gepch.h"
#include "Tests.h"

namespace TESTS
{
	void Menu::onImgui()
	{
		Test::onImgui();
		for (auto& test : tests)
		{
			if (ImGui::Button(test.first.c_str()))
			{
				currTest = (std::shared_ptr<Test>) test.second();
			}
		}
	}

	Menu::~Menu()
	{
	}

	Test::Test(std::string name, App::Game& game) : name(name), game(game)
	{
		game.getWindow().getCamera()->onWindowResize();
	}

	void Test::onImgui()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	ImVec2 Test::getImWindowPosition()
	{
		ImGuiWindow* window = getImWindow();
		return window->Pos;
	}
	ImVec2 Test::getImWindowSize()
	{
		return getImWindow()->Size;
	}
	ImGuiWindow* Test::getImWindow()
	{
		ImGuiContext* context = ImGui::GetCurrentContext();
		return context->CurrentWindow;
	}
}