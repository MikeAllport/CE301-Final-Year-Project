#include "CppUnitTest.h"
#include "RendererTest.h"
#include <GE/Graphics/TextureCache.h>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GameEngineUnitTest
{


	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(TestFalseModelNotSet)
		{
			GE::Window window = GE::Window();
			GE::Graphics::Renderer* rend = new GE::Graphics::RendererBatched("batchedRendererTest-vert.shader", "batchedRendererTest-frag.shader");
			glm::mat4 projection = glm::perspective(glm::radians(45.0f), 2 / (float)2, 1.f, -1.f);
			Assert::IsFalse(rend->isQuadInFrustrum(1, 1, 1, 1, 1, 1));
		}

		TEST_METHOD(TestIsInFrustrum1)
		{
			GE::Window window = GE::Window();
			GE::Graphics::Renderer* rend = new GE::Graphics::RendererBatched("batchedRendererTest-vert.shader", "batchedRendererTest-frag.shader");
			glm::mat4 projection = glm::perspective(glm::radians(45.0f), 2 / (float)2, 1.f, -1.f);
			rend->setProjectionMatrix(projection);
			Assert::IsTrue(rend->isQuadInFrustrum(0, 0, 0, 1, 1, 1));
		}

		TEST_METHOD(TestIsNotInFrustrumXOut)
		{
			GE::Window window = GE::Window();
			GE::Graphics::Renderer* rend = new GE::Graphics::RendererBatched("batchedRendererTest-vert.shader", "batchedRendererTest-frag.shader");
			glm::mat4 projection = glm::perspective(glm::radians(45.0f), 2 / (float)2, 1.f, -1.f);
			rend->setProjectionMatrix(projection);
			Assert::IsFalse(rend->isQuadInFrustrum(1, 0, 0, 1, 1, 1));
		}
	};
}
