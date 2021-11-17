#ifndef GE_BASEAPP
#define GE_BASEAPP

#include "Window.h"
#include "GE/Graphics/Shader.h"
#include "Graphics/TextureCache.h"
#include "Camera.h"
#include "MousePosition.h"
#include "Clock.h"


/**
* base application, provides functions and members that any application wanting
* to use GameEngine must realise and implement.
*
* Its purpose it to provide delta t calculations (timeElapsed is time between frames) and
* create the window context, handle closing the window and resizes
*/
//TODO: get vsync disabled working without forcing sing buffer mode

using CamType = GE::CamType;
namespace GE
{
	class BaseApp: public EventHandler
	{
	public:
		BaseApp(WindowProps props = WindowProps());
		virtual ~BaseApp();
		virtual void run() = 0;
		virtual void onEvent(Event& e) override;
		void onUpdate();
		static float timePassedMS();
		static BaseApp& getApp();
		Window& getWindow();
		std::string fps = "0fps";
	protected:
		GE::Clock dtClock, fpsClock;
		std::unique_ptr<Window> window = nullptr;
		bool isRunning = true;
		uint64 initTime = 0;
		static double timeElapsed;
	private:
		void updateFps();
		void updateDT();
		int frames = 0;
		static BaseApp* app;
	};

}

#endif // !GE_BASEAPP
