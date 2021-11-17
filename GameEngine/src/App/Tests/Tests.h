#ifndef APP_TESTS
#define APP_TESTS

#include "GE/Window.h"
#include "gepch.h"
#include <imgui/imgui.h>
#include "GE/BaseApp.h"
#include <App/Game.h>
#include <imgui/imgui_internal.h>
#include <GE/Events/EventHandler.h>

namespace TESTS
{
	/**
	* Test's purpose is to descrive virtual functions that child classes will overwrite, namesly update render and
	* onImgui which are all part of the game loop. Each realised derrived class will have different implementations
	* specific to that test, i.e rendering some quads, using a specific camera etc
	*/
	class Test: public GE::EventHandler
	{
	public:
		Test(std::string name, App::Game& game);
		~Test() { game.gameWindowActive = false; }

		virtual void onUpdate(float dt) {};
		virtual void onRender() {};
		virtual void onImgui();
		ImVec2 getImWindowPosition();
		ImVec2 getImWindowSize();
		
		std::string name = "";
		App::Game& game;

		// Inherited via EventHandler
		virtual void onEvent(GE::Event& e) override {};
	private:
		ImGuiWindow* getImWindow();

	};

	/**
	* TestMenu's purpose is to set the currently selected test, hold a cache of tests,
	*/
	class Menu : public Test
	{
	public:
		Menu(std::shared_ptr<Test>& placeholder, App::Game& game) : Test("Tests", game), currTest(placeholder), tests() {};
		~Menu();

		void onImgui();

		template<typename T>
		void pushTest(const std::string name, App::Game& game)
		{
			GE_INFO("IMGUI Adding test: {0}", name);
			tests.push_back(std::make_pair(name, [name, &game]() { return std::shared_ptr<T>(new T(name, game)); }));
		};
	private:
		std::shared_ptr<Test>& currTest;
		std::vector<std::pair<std::string, std::function<std::shared_ptr<Test> ()>>> tests;
	};
}
#endif // !APP_TESTS
