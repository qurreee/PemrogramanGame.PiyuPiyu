#include "DinoMain.h"

Engine::DinoMain::DinoMain(Setting* setting) :Engine::Game(setting)
{
	setting->windowTitle = "Dino Game but with Chicken";
}

Engine::DinoMain::~DinoMain()
{
}

void Engine::DinoMain::Init()
{
	Engine::ScreenManager::GetInstance(this)->AddScreen("dinogame", new DinoDino())
		->AddScreen("mainmenu", new DinoGUI())->SetCurrentScreen("mainmenu");
}

void Engine::DinoMain::Update()
{
	Engine::ScreenManager::GetInstance(this)->Update();
}

void Engine::DinoMain::Render()
{
	Engine::ScreenManager::GetInstance(this)->Draw();
}
