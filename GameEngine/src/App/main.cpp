#include "gepch.h"
#include "App/Game.h"
#include <App/Tests/TestGame.h>
#include <stdlib.h>
#include <crtdbg.h>

int main(int argc, char argv[])
{
//#ifdef GE_DEBUG
//	App::TestGame game;
//	GE::BaseApp::getApp().run();
//#else
	App::Game game;
	GE::BaseApp::getApp().run();
//#endif
}