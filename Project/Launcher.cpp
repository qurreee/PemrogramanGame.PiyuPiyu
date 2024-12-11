#include "Setting.h"
#include "Game.h"

#include "PPManager.h"

int main(int argc, char** argv) {
	Engine::Setting* setting = new Engine::Setting();
	setting->screenWidth = 1920; 
	setting->screenHeight = 1080;
	setting->windowFlag = Engine::WindowFlag::WINDOWED;
	setting->vsync = true;
	setting->targetFrameRate = 30;
	Engine::Game* game = new Engine::PPManager(setting);
	game->Run();
	delete setting;
	delete game;
		
	return 0;
}
