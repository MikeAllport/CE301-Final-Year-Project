#include "CppUnitTest.h"
#include <GE/Camera.h>
#include <App/MouseState.h>
#include <GE/Graphics/Renderer.h>
#include <App/Sprite.h>
#include <App/Game.h>
#include <App/WorldGeneration/Tile.h>
#include "MouseStateTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GameEngineUnitTest
{
	TEST_CLASS(MouseStateTest)
	{
	public:
		GE::WindowProps windowProps;
		GE::Window window;
		MouseStateTest() : windowProps(), window(windowProps)
		{
			window.setCamera(GE::CamType::PERSPECTIVE);
			window.getCamera()->setPosition(glm::vec3(0, 0, 0));
			window.getCamera()->onWindowResize();
		}

		TEST_METHOD(GetMouseToWorld16384x16384)
		{
			window.getCamera()->setPosition(glm::vec3(std::pow(App::Tile::TILE_HEIGHT, 2), 0, std::pow(App::Tile::TILE_HEIGHT, 2)));
			App::Vector2D position(windowProps.width / 2, windowProps.height / 2);
			glm::vec3 worldPos = App::MouseState::getScreenToWorldPosition(window, App::Vector2D(position.x, position.y));
			Assert::IsTrue(worldPos.x == 16384 && worldPos.z == 16384);
		}

		TEST_METHOD(GetMouseToWorld00)
		{
			App::Vector2D position(windowProps.width / 2, windowProps.height / 2);
			glm::vec3 worldPos = App::MouseState::getScreenToWorldPosition(window, App::Vector2D(position.x, position.y));
			Assert::IsTrue(worldPos.x == 0 && worldPos.z == 0);
		}

		TEST_METHOD(GetMouseToWorld16384x0)
		{
			window.getCamera()->setPosition(glm::vec3(std::pow(App::Tile::TILE_HEIGHT, 2), 0, 0));
			App::Vector2D position(windowProps.width / 2, windowProps.height / 2);
			glm::vec3 worldPos = App::MouseState::getScreenToWorldPosition(window, App::Vector2D(position.x, position.y));
			Assert::IsTrue(worldPos.x == 16384 && worldPos.z == 0);
		}

		TEST_METHOD(GetMouseToWorld0x16384)
		{
			window.getCamera()->setPosition(glm::vec3(0, 0, std::pow(App::Tile::TILE_HEIGHT, 2)));
			App::Vector2D position(windowProps.width / 2, windowProps.height / 2);
			glm::vec3 worldPos = App::MouseState::getScreenToWorldPosition(window, App::Vector2D(position.x, position.y));
			Assert::IsTrue(worldPos.x == 0 && worldPos.z == 16384);
		}
	};

}