#include "CppUnitTest.h"
#include <App/TextureMap.h>
#include <GE/Window.h>
#include <App/WorldGeneration/GeneratorSettings.h>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GameEngineUnitTest
{
	TEST_CLASS(TextureMapTest)
	{
	public:
		GE::Window window;
		App::TexturePack pack, pack2;
		TextureMapTest() :
			window(),
			pack(App::TexturePacks::get(App::TextureNameEnums::TEXT_CHARACTER)),
			pack2(App::TexturePacks::get(App::TextureNameEnums::TEXT_CHARACTER))
		{};
		TEST_METHOD(DoesEqual)
		{
			Assert::IsTrue(pack == pack2);
		}

		TEST_METHOD(NotEqualDiffTexture)
		{
			App::TexturePack diffTexturedPack =
				App::TexturePacks::get(App::TextureNameEnums::TEXT_DIRT);
			pack2.text = diffTexturedPack.text;
			Assert::IsFalse(pack2 == pack);
		}

		TEST_METHOD(NotEqualDiffWidth)
		{
			Assert::IsTrue(pack == pack2);
			pack2.textWidth = 0;
			Assert::IsFalse(pack == pack2);
		}

		TEST_METHOD(NotEqualDiffHeight)
		{
			Assert::IsTrue(pack == pack2);
			pack2.textHeight = 0;
			Assert::IsFalse(pack == pack2);
		}

		TEST_METHOD(NotEqualDiffOffsets)
		{
			Assert::IsTrue(pack == pack2);
			pack2.textOffset = glm::vec3(-1,-1,-1);
			Assert::IsFalse(pack == pack2);
		}
	};
}