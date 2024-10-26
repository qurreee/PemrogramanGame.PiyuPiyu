#include "Lesson07_GUI.h"

Engine::Lesson07_GUI::Lesson07_GUI(Setting* setting) :Engine::Game(setting)
{
	setting->windowTitle = "GUI Demo";
}

Engine::Lesson07_GUI::~Lesson07_GUI()
{
}

void Engine::Lesson07_GUI::Init()
{
	Engine::ScreenManager::GetInstance(this)->AddScreen("ingame", new InGameScreen())
		->AddScreen("mainmenu", new MainMenuScreen())->SetCurrentScreen("mainmenu");
}

void Engine::Lesson07_GUI::Update()
{
	Engine::ScreenManager::GetInstance(this)->Update();
}

void Engine::Lesson07_GUI::Render()
{
	Engine::ScreenManager::GetInstance(this)->Draw();
}





