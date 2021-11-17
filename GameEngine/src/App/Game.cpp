#include "gepch.h"
#include "App/Game.h"
#include <App/Layers/WorldLayer.h>
#include <App/Layers/MenuLayer.h>


#define _CRTDBG_MAP_ALLOC

namespace App
{

	Game::Game() : BaseApp(),
		worldLayer(nullptr)
	{
		TexturePacks::init();
		addEventCategory(GE::EventCategory::Application);
		addEventCategory(GE::EventCategory::Keyboard);
		addEventCategory(GE::EventCategory::Mouse);
		worldLayer = std::make_unique<WorldLayer>(*window.get(), *this);
		menuLayer = std::make_unique<MenuLayer>(*worldLayer, *this);
		layers.push_back(std::dynamic_pointer_cast<ILayer>( menuLayer));
		layers.push_back(std::dynamic_pointer_cast<ILayer>(worldLayer));
	}

	Game::~Game()
	{
	}

	CharacterObject& Game::getCharacter()
	{
		return *worldLayer.get()->character;
	}

	void Game::onEvent(GE::Event& e)
	{
		BaseApp::onEvent(e);
		for (auto layer : layers)
		{

			layer.get()->onEvent(e);
		}
	}

	void Game::run()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		std::vector<int> vec;
		while (isRunning)
		{
			for (std::vector<std::shared_ptr<ILayer>>::iterator it = layers.begin(); it != layers.end(); it++)
			{
				(*it).get()->onUpdate(timeElapsed);
			}
			for (std::vector<std::shared_ptr<ILayer>>::reverse_iterator it = layers.rbegin(); it != layers.rend(); it++)
			{
				(*it).get()->onRender();
			}
			for (std::vector<std::shared_ptr<ILayer>>::iterator it = layers.begin(); it != layers.end(); it++)
			{
				if ((*it).get()->isDead)
					it = layers.erase(it);
			}
			onUpdate();
		}
	}

	void Game::onUpdate()
	{
		BaseApp::onUpdate();
	}
}