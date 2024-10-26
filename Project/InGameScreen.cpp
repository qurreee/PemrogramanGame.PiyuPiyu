#include "InGameScreen.h"

Engine::InGameScreen::InGameScreen() 
{
}

void Engine::InGameScreen::Init()
{
	// Spawn setting
	maxSpawnTime = 300;
	numObjectPerSpawn = 1;
	numObjectsInPool = 50;

	// Load a texture
	Texture* texture = new Texture("turtles.png");
	for (int i = 0; i < numObjectsInPool; i++) {
		Turtle* o = new Turtle(CreateSprite(texture));
		objects.push_back(o);
	}

	// Add input mappings
	game->GetInputManager()->AddInputMapping("mainmenu", SDLK_ESCAPE);

}

void Engine::InGameScreen::Update()
{
	// Back to main menu
	if (game->GetInputManager()->IsKeyReleased("mainmenu")) {
		ScreenManager::GetInstance(game)->SetCurrentScreen("mainmenu");
	}

	// Set background
	game->SetBackgroundColor(235, 229, 52);

	// Time to spawn objects
	if (spawnDuration >= maxSpawnTime) {
		SpawnObjects();
		spawnDuration = 0;
	}
	// Update all objects
	for (Turtle* o : objects) {
		o->Update((game->GetGameTime()));
	}
	// Count spawn duration
	spawnDuration += (game->GetGameTime());

}

void Engine::InGameScreen::Draw()
{
	// Render all objects
	for (Turtle* o : objects) {
		o->Draw();
	}
}

Engine::Sprite* Engine::InGameScreen::CreateSprite(Texture* texture)
{
	return (new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetNumXFrames(14)->SetNumYFrames(4)->AddAnimation("hit", 2, 4)
		->AddAnimation("spikes", 5, 12)->AddAnimation("idle-1", 14, 27)->AddAnimation("idle-2", 28, 41)
		->AddAnimation("spikes-out", 42, 49)->PlayAnim("spikes")->SetScale(1.5)->SetAnimationDuration(100);
}

void Engine::InGameScreen::SpawnObjects()
{
	//Find Die object to reuse for spawning
	int spawnCount = 0;
	for (Turtle* o : objects) {
		if (spawnCount == numObjectPerSpawn) {
			break;
		}
		if (o->IsDie()) {
			// Set state to spawn
			
			// Random spawn position
			int min = 0;
			int max = (int) (game->GetSettings()->screenWidth - o->GetWidth());
			float x = (float) (rand() % (max - min + 1) + min);
			float y = game->GetSettings()->screenHeight + o->GetHeight();
			o->SetSpawn()->SetPosition(x, y);
			spawnCount++;
		}
	}
}

