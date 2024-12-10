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
	Engine::ScreenManager::GetInstance(this)->AddScreen("ingame", new PPGame())->AddScreen("menu", new PPMenu())->AddScreen("gameover", new PPScoreBoard())->SetCurrentScreen("menu");
}

void Engine::PPManager::Update()
{
	Engine::ScreenManager::GetInstance(this)->Update();
}

void Engine::PPManager::Render()
{
	Engine::ScreenManager::GetInstance(this)->Draw();
}
