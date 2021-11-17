#ifndef _APP_WORLDLAYER
#define _APP_WORLDLAYER

#include <GE/Window.h>
#include <GE/Graphics/Renderer.h>
#include <GE/Graphics/FontRenderer.h>

#include <App/Layers/ILayer.h>
#include <App/CameraEventHandler.h>
#include <App/Controller.h>
#include <App/ClickHandler.h>
#include <App/WorldGeneration/World.h>
#include <App/WorldGeneration/ObjectGenerator.h>
#include <App/GameObject.h>
#include <App/ObjectPicker.h>
#include <App/StencilDrawer.h>
#include <App/Game.h>
#include <App/WorldGeneration/GeneratorSettings.h>

using namespace App::WorldGen;
namespace App
{
	extern class CharacterObject;
	class WorldLayer :	public ILayer
	{
	public:
		WorldLayer(GE::Window& window, Game& game);
		void onRender() override;
		void onUpdate(const float& delta) override;
		void onEvent(GE::Event& e);
		void initCharacter();
		void initWorld();
		void initCamHandler();
		void initObjects();
		// size must be to the base 2 i.e 2^4, 2^5, 2^6
		const static int WORLD_SIZE_WH = 256;
		std::unique_ptr<CharacterObject> character;
	private:
		friend class MenuLayer;
		void renderFont(float x, float y, float size, std::string text);
		void setCameraHandler();
		Controller keyController;

		GE::Window& window;
		GE::Graphics::FontRenderer& fontRenderer;

		std::unique_ptr<ClickHandler> clickHandler;
		std::unique_ptr<Camera3DHandler> camHandler;
		std::unique_ptr<World> world;
		Game& game;

		// gameobject stuff
		std::vector<CommonGameObject*> gameObjects;
		std::unique_ptr<WorldGen::ObjectGenerator> objectGenerator;
		std::unique_ptr<ObjectPicker> objectPicker;

		// renderer stuff
		std::unique_ptr<GE::Graphics::RendererBatched> renderer;
		StencilDrawer stencilRend;

		// world stuff
		WorldGen::ObjectPlacementSettings objectSettings;
		WorldGen::MapSettings mapSettings;

		inline static const std::string batchedRendVert = "batchedRendererTest-vert.shader",
			batchedRendFrag = "batchedRendererTest-frag.shader";
	};

}
#endif // !_APP_WORLDLAYER
