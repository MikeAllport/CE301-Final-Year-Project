#include "CppUnitTest.h"
#include "SpriteTest.h"
#include <GE/Camera.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GameEngineUnitTest
{
	TEST_CLASS(SpriteTest)
	{
	public:
		GE::Window window;
		GE::PerspectiveCamera cam;
		RendererStub rendStub;
		GameObjectStub objStub;
		SpriteTest() : 
			window(), 
			cam(window),
			rendStub(),
			objStub(){};
		TEST_METHOD(SetModelMatrixSetsMatrix)
		{
			glm::mat4 spriteModelM = objStub.sprite.getModelMatrix();
			Assert::IsTrue(spriteModelM == objStub.sprite.getModelMatrix());
			Assert::IsTrue(objStub.getMoved());
			Assert::IsFalse(rendStub.modelBeenSet());
			objStub.sprite.setModelMatrix(rendStub);
			Assert::IsTrue(spriteModelM != objStub.sprite.getModelMatrix());
			Assert::IsFalse(objStub.getMoved());
			Assert::IsTrue(rendStub.modelBeenSet());
		}

		TEST_METHOD(SetTextureChangesTexture)
		{
			Assert::IsTrue(objStub.sprite.getTexturePack() ==
				App::TexturePacks::get(App::TextureNameEnums::TEXT_CHARACTER));
			objStub.sprite.setTexture(App::TextureNameEnums::TEXT_DIRT);
			Assert::IsFalse(objStub.sprite.getTexturePack() ==
				App::TexturePacks::get(App::TextureNameEnums::TEXT_CHARACTER));
		}

		TEST_METHOD(DrawDraws)
		{
			Assert::IsFalse(rendStub.quadDrawn);
			objStub.sprite.draw(rendStub);
			Assert::IsTrue(rendStub.quadDrawn);
		}
	};
}