#include "gepch.h"
#include "BaseApp.h"
#ifdef _WIN32
#include <Windows.h>
#include <time.h>
#else
#include <unistd.h>
#endif

namespace GE
{
	GE::BaseApp* BaseApp::app = nullptr;

	double BaseApp::timeElapsed = 0.0;

	BaseApp::BaseApp(WindowProps props) : EventHandler(),
		dtClock(),
		fpsClock()
	{
		Clock now;
		initTime = now.epochMS;
		app = this;
		window = std::make_unique<GE::Window>(props);
		MousePosition::SetMouse(window->getGLFWWindow());
		glfwSetTime(0);
	}

	BaseApp::~BaseApp()
	{
	}

	void BaseApp::onUpdate()
	{
		window->onUpdate();
		updateFps();
		updateDT();
	}

	void BaseApp::updateDT()
	{
		Clock now;
		uint64 dtDiff = dtClock.timeDiffMS(now);
		dtClock.reset();
		timeElapsed = dtDiff / 1000.f;
	}

	void BaseApp::updateFps()
	{
		Clock now;
		uint64 timeDiff = fpsClock.timeDiffMS(now);
		if (timeDiff >= 1000)
		{
			fps = std::to_string(frames * 1000 / timeDiff) + "fps";
			fpsClock.reset();
			frames = 0;
		}
		else
			++frames;
	}

	void BaseApp::onEvent(Event& e)
	{
		switch (e.getType())
		{
		case GE::EventType::WindowClose:
		{
			isRunning = false;
			break;
		}
		case GE::EventType::WindowResize:
		{
			window->getCamera()->onWindowResize();
		}
		}
	}

	float BaseApp::timePassedMS()
	{
		return timeElapsed * 1000;
	}

	BaseApp& BaseApp::getApp()
	{
		return *app;
	}

	Window& BaseApp::getWindow()
	{
		return *window;
	}
}