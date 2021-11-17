#ifndef APP_GAME
#define APP_GAME

#include "gepch.h"
#include "GE/BaseApp.h"
#include "GE/Events/Keys/KeyEvent.h"
#include "GE/Events/EventHandler.h"
#include "GE/Events/Event.h"


#include "GE/Clock.h"
#include "CharacterObject.h"
#include <App/Interfaces.h>
#include <App/Layers/ILayer.h>

namespace TESTS
{
	class WorldTileTest;
}

namespace App
{
	extern class WorldLayer;
	extern class MenuLayer;
	using KEYS = GE::Keys;
	enum KeyBindings
	{
		CAMERA_MOVE_UP = KEYS::UP,
		CAMERA_MOVE_DOWN = KEYS::DOWN,
		CAMERA_MOVE_RIGHT = KEYS::LEFT,
		CAMERA_MOVE_LEFT = KEYS::RIGHT,
		CHARACTER_MOVE_UP = KEYS::W,
		CHARACTER_MOVE_DOWN = KEYS::S,
		CHARACTER_MOVE_LEFT = KEYS::A,
		CHARACTER_MOVE_RIGHT = KEYS::D
	};

	// base class entry point
	class Game : public GE::BaseApp, public IUpdateable
	{
	public:
		Game();
		virtual ~Game();

		// game loop here
		virtual void run() override;
		void onUpdate() override;
		void onCharacterReset();
		CharacterObject& getCharacter();

		static inline int WORLD_SIZE_WH = 0;
		//TODO: Event handler function
		//event handler function
		void onEvent(GE::Event& e) override;
		GE::Clock frameStart;
		bool gameWindowActive = false;

	private:
		std::shared_ptr<WorldLayer> worldLayer;
		std::shared_ptr<MenuLayer> menuLayer;
		std::vector<std::shared_ptr<ILayer>> layers;
	};
}
#endif // !APP_GAME
