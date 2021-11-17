#include "CppUnitTest.h"
#include "WindowTest.h"
#include <GE/Camera.h>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GameEngineUnitTest
{
	TEST_CLASS(WindowPropsTest)
	{
	public:
		TEST_METHOD(TestDefaultConstructor)
		{
			GE::WindowProps props;
			Assert::AreEqual(std::string("GameEngine Window"), props.title);
			Assert::AreEqual(1200, props.width);
			Assert::AreEqual(780, props.height);
			Assert::IsTrue(props.VSync);
			
		}

		TEST_METHOD(TestNewConstructor)
		{
			std::string title = "Test Title";
			int width = 1000;
			int height = width;
			GE::WindowProps props(title, width, height);
			Assert::AreEqual(title, props.title);
			Assert::AreEqual(width, props.width);
			Assert::AreEqual(height, props.height);
		}
	};

	TEST_CLASS(WindowTest)
	{
	public:
		GE::WindowProps windowProps;
		GE::Window window;
		WindowTest() : windowProps(), window(windowProps) {};
		TEST_METHOD(TestWindowConstructor)
		{
			Assert::AreEqual((uint32)windowProps.height, window.getHeight());
			Assert::AreEqual((uint32)windowProps.width, window.getWidth());
		}

		TEST_METHOD(TestWindowInitilization)
		{
			int width, height;
			std::string title;
			GLFWwindow* wind = window.getGLFWWindow();
			glfwGetWindowSize(wind, &width, &height);
			Assert::AreEqual(windowProps.width, width);
			Assert::AreEqual(windowProps.height, height);
		}

		TEST_METHOD(TestOnResizeSetsSize)
		{
			int newWidth = 1000, newHeight = 1000;
			GLFWwindow* wind = window.getGLFWWindow();
			glfwSetWindowSize(wind, newWidth, newHeight);
			window.onUpdate();
			Assert::AreEqual((uint32)newWidth, window.getWidth());
			Assert::AreEqual((uint32)newHeight, window.getHeight());
		}

		TEST_METHOD(TestSetCameraSwitchesCameras)
		{
			GE::Camera2D* orthoCam = dynamic_cast<GE::Camera2D*>(window.getCamera().get());
			Assert::IsNotNull(orthoCam);
			window.setCamera(GE::CamType::PERSPECTIVE);
			GE::PerspectiveCamera* perspCam = dynamic_cast<GE::PerspectiveCamera*>(window.getCamera().get());
			Assert::IsNotNull(perspCam);
			window.setCamera(GE::CamType::ORTHO); 
			orthoCam = dynamic_cast<GE::Camera2D*>(window.getCamera().get());
			Assert::IsNotNull(orthoCam);
		}

	};

}