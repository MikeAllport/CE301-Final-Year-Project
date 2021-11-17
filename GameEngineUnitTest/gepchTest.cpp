#include "CppUnitTest.h"
#include <glm.hpp>
#include <gepch.h>
#include <App/WorldGeneration/GeneratorSettings.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GameEngineUnitTest
{
	TEST_CLASS(gepchTest)
	{
	public:

		glm::mat4 mat;
		gepchTest() : mat(1.0f) {};
		TEST_METHOD(GetMat4RowGetsRow)
		{
			Assert::IsTrue(getMat4Row(mat, 0) == glm::fvec4(1, 0, 0, 0));
		}

		TEST_METHOD(GetMat4RowFails)
		{
			try
			{
				getMat4Row(mat, 4);
				Assert::IsTrue(false);
			}
			catch (...)
			{
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(SetMat4RowWorks)
		{
			glm::fvec4 vec(1, 1, 1, 1);
			mat = setMat4Row(mat, vec, 0);
			Assert::IsTrue(getMat4Row(mat, 0) == vec);
		}

		TEST_METHOD(GetMat4ColumnsWorks)
		{
			Assert::IsTrue(getMat4Column(mat, 0) == glm::fvec4(1, 0, 0, 1));
		}

		TEST_METHOD(GetMat4ColFails)
		{
			try
			{
				getMat4Column(mat, 4);
				Assert::IsTrue(false);
			}
			catch (...)
			{
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(SetMat4ColumnWorks)
		{
			glm::fvec4 vec(1, 1, 1, 1);
			mat = setMat4Column(mat, vec, 0);
			Assert::IsTrue(getMat4Column(mat, 0) == vec);
		}
	};
}