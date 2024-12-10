#include "ScreenManager.h"

Engine::ScreenManager* Engine::ScreenManager::instance = new ScreenManager();


Engine::ScreenManager::ScreenManager()
{
	engine = nullptr;
	currentScreen = nullptr;
}

void Engine::ScreenManager::Update()
{
	if (currentScreen == nullptr) return;
	currentScreen->Update();
}

void Engine::ScreenManager::Draw()
{
	 if (currentScreen == nullptr) return;

    try {
        currentScreen->Draw();
    } catch (const std::exception& e) {
        std::cerr << "Error in Screen::Draw: " << e.what() << std::endl;
    }
}

Engine::ScreenManager* Engine::ScreenManager::AddScreen(string name, Screen* screen)
{
	if (!engine) {
		std::cerr << "Error: engine is nullptr!" << std::endl;
		return this; // Early exit to avoid further issues
	}
	screen->SetGame(engine);
	screens.insert(pair<string, Screen*>(name, screen));
	return this;
}

Engine::ScreenManager* Engine::ScreenManager::SetCurrentScreen(string name)
{
    // Simpan referensi ke layar saat ini sebelum mengganti layar
    Screen* oldScreen = currentScreen;

    // Set layar baru sebagai layar saat ini
    currentScreen = screens[name];

    // Inisialisasi layar baru
    if (currentScreen != nullptr) {
        currentScreen->Init();
    }

    // Bersihkan layar lama setelah mengganti layar
    if (oldScreen != nullptr) {
        oldScreen->CleanUp();
    }

    return this;
}


Engine::Screen* Engine::ScreenManager::GetCurrentScreen()
{
	return currentScreen;
}

Engine::Game* Engine::ScreenManager::GetGame()
{
	return engine;
}

Engine::ScreenManager* Engine::ScreenManager::SetGame(Game* engine)
{
	this->engine = engine;
	return this;
}

Engine::ScreenManager* Engine::ScreenManager::GetInstance(Game* engine)
{
	return Engine::ScreenManager::instance->SetGame(engine);
}
