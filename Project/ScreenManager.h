#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "Game.h"
#include "Screen.h"
#include <unordered_map>

namespace Engine {
	class ScreenManager
	{
	public:
		ScreenManager(const ScreenManager& obj) = delete;
		static Engine::ScreenManager* GetInstance(Game* engine);
		void Update();
		void Draw();
		ScreenManager* AddScreen(string name, Screen* screen);
		ScreenManager* SetCurrentScreen(string name);
		Screen* GetCurrentScreen();
		Game* GetGame();
	    ScreenManager* SetGame(Game* engine);
	private:
		ScreenManager();
		unordered_map<string, Screen*> screens;
		Game* engine;
		Screen* currentScreen;
		static Engine::ScreenManager* instance;
	};
}

#endif
