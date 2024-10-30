#include "PPManager.h"

Engine::PPManager::PPManager(Setting* setting) :Engine::Game(setting)
{
	setting->windowTitle = "Piyu - Piyu";
}

Engine::PPManager::~PPManager()
{
}

void Engine::PPManager::Init()
{
	std::cout << "test1" << std::endl;
	Engine::ScreenManager::GetInstance(this)->AddScreen("ingame1", new PPGame())->SetCurrentScreen("ingame1");
	std::cout << "test24" << std::endl;
}

void Engine::PPManager::Update()
{
	Engine::ScreenManager::GetInstance(this)->Update();
}

void Engine::PPManager::Render()
{
	Engine::ScreenManager::GetInstance(this)->Draw();
}
