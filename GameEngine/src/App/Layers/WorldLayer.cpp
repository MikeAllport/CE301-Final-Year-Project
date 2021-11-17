#include <gepch.h>
#include "WorldLayer.h"

namespace App
{
	WorldLayer::WorldLayer(GE::Window& window, Game& game) :
		window(window),
		game(game),
		fontRenderer(GE::Graphics::FontRenderer::getInstance()),
		renderer(nullptr),
		keyController(),
		camHandler(nullptr),
		character(nullptr),
		world(nullptr),
		clickHandler(nullptr),
		objectGenerator(nullptr),
		stencilRend(),
		objectPicker(nullptr)
	{
		initCharacter();
		world = std::make_unique<World>(WORLD_SIZE_WH);
		initWorld();
		initCamHandler();
		clickHandler = std::make_unique<ClickHandler>(window, *character.get());
		initObjects();
		window.setCamera(GE::CamType::PERSPECTIVE);
	}

	void WorldLayer::initCharacter()
	{
		character = std::make_unique<CharacterObject>(
			glm::vec3(
				WORLD_SIZE_WH * Tile::TILE_WIDTH / 2,
				0,
				WORLD_SIZE_WH * Tile::TILE_HEIGHT / 2),
			keyController);
	}

	void WorldLayer::initWorld()
	{
		renderer = std::make_unique<GE::Graphics::RendererBatched>(std::string(batchedRendVert), std::string(batchedRendFrag));
		world->generateWorld(mapSettings);
		world->drawStaticContent(*renderer);
	}

	void WorldLayer::initCamHandler()
	{
		window.setCamera(GE::CamType::PERSPECTIVE);
		camHandler = std::make_unique<Camera3DHandler>(window.getCamera(), *character.get());
		camHandler.get()->setCameraPosition(character.get()->getPosition());
	}

	void WorldLayer::initObjects()
	{
		gameObjects.clear();
		objectPicker = std::make_unique<ObjectPicker>(game);
		objectGenerator = std::make_unique<ObjectGenerator>(*world.get(), objectSettings);
		for (CommonGameObject* obj : *objectGenerator.get()->getObjects())
			gameObjects.push_back(obj);
		gameObjects.push_back(character.get());
	}

	void WorldLayer::onRender()
	{
		int objectsCulled = 0;
		glm::mat4 projection = window.getCamera()->getViewProjection();
		// sort objects
		std::vector<CommonGameObject*> drawables;
		drawables.reserve(gameObjects.size());
		renderer.get()->setProjectionMatrix(projection);
		std::sort(gameObjects.begin(), gameObjects.end(), [](CommonGameObject* first, CommonGameObject* second) -> bool
			{
				return *first < *second;
			});
		for (std::vector<CommonGameObject*>::iterator it = gameObjects.begin();
			it != gameObjects.end();
			++it)
		{
			if ((*it)->getSprite().isRenderable(*renderer.get()))
			{
				drawables.push_back(*it);
			}
			else objectsCulled++;
		}

		// set object under mouse
		objectPicker.get()->pickObjects(&drawables);
		// draw objects with stencil
		window.useMainWindow();
		renderer.get()->begin();
		renderer.get()->setProjectionMatrix(projection);
		for (std::vector<CommonGameObject*>::iterator it = drawables.begin();
			it != drawables.end();
			++it)
		{
			if (*it == MouseState::objectUnderMouse)
				stencilRend.draw(*it, projection, *renderer.get());
			else
				(*it)->draw(*renderer.get());
		}

		renderer.get()->end();
		// render font
		//fontRenderer.setFont("res\\fonts\\", "arial.ttf");
		//fontRenderer.setColor(glm::vec3(1, 0, 0));
		//std::stringstream ss;
		//ss << std::hex << world->rng.getSeed();
		//std::string seed = ss.str();
		//float x = -1.0f, y = 0.9f, s = 0.1f;
		//renderFont(x, y, s, (game.fps + " " + seed).c_str());
		//y -= 0.1;
		//renderFont(x, y, s, ("Objects culled: " + std::to_string(objectsCulled)));
	}

	void WorldLayer::onUpdate(const float& delta)
	{
		Camera3DHandler* handler3d = dynamic_cast<Camera3DHandler*>(camHandler.get());
		camHandler->onUpdate(delta);
		keyController.onUpdate();
		character->onUpdate(delta);
	}
	void WorldLayer::onEvent(GE::Event& e)
	{
		if (e.isHandled())
			return;
		if (e.getType() == GE::EventType::MouseScrolled)
			camHandler->onMouseEvent(e);
		else if (e.getType() == GE::EventType::MouseButPressed)
		{
			clickHandler.get()->onMouseEvent(e);
		}
	}
	void WorldLayer::renderFont(float x, float y, float size, std::string text)
	{
		auto textCstr = text.c_str();
		fontRenderer.begin();
		fontRenderer.renderText(textCstr, x, y, size);
		fontRenderer.end();
	}
	void WorldLayer::setCameraHandler()
	{
	}
}