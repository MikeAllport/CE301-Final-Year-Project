#include "CppUnitTest.h"
#include <Object.h>
#include <App/WorldGeneration/GeneratorSettings.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GameEngineUnitTest
{
	class ObjectStub : public GE::Object
	{
	public:

		// Inherited via Object
		virtual std::string toString() const override
		{
			return "I am a test stub";
		}
	};

	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestOperatorOstream)
		{
			std::ostringstream stream;
			ObjectStub stub;
			stream << stub;
			Assert::AreEqual(stub.toString(), stream.str());
		}
	};
}
