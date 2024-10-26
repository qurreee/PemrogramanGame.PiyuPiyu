#include "Lesson06_ObjectPool.h"

Engine::Lesson06_ObjectPool::Lesson06_ObjectPool(Setting* setting) :Engine::Game(setting)
{
	setting->windowTitle = "Object Pool";
}

Engine::Lesson06_ObjectPool::~Lesson06_ObjectPool()
{
	delete texture;
}

void Engine::Lesson06_ObjectPool::Init()
{
	// Spawn setting
	maxSpawnTime = 300;
	numObjectPerSpawn = 1;
	numObjectsInPool = 100;

	// Load a texture
	texture = new Texture("turtles.png");
	for (int i = 0; i < numObjectsInPool; i++) {
		Turtle* o = new Turtle(CreateSprite());
		objects.push_back(o);
	}
	// Set background
	SetBackgroundColor(235, 229, 52);

	// Add input
	inputManager->AddInputMapping("quit", SDLK_ESCAPE);
}

void Engine::Lesson06_ObjectPool::Update()
{
	if (inputManager->IsKeyReleased("quit")) {
		state = Engine::State::EXIT;
	}
	// Time to spawn objects
	if (spawnDuration >= maxSpawnTime) {
		SpawnObjects();
		spawnDuration = 0;
	}
	// Update all objects
	for (Turtle* o : objects) {
		o->Update(GetGameTime());
	}
	// Count spawn duration
	spawnDuration += GetGameTime();
}

void Engine::Lesson06_ObjectPool::Render()
{
	// Render all objects
	for (Turtle* o : objects) {
		o->Draw();
	}
}

/*
* Helper method to create a custom sprite
*/
Engine::Sprite* Engine::Lesson06_ObjectPool::CreateSprite()
{
	return (new Sprite(texture, defaultSpriteShader, defaultQuad))->SetNumXFrames(14)->SetNumYFrames(4)->AddAnimation("hit", 2, 4)->AddAnimation("spikes", 5, 12)->AddAnimation("idle-1", 14, 27)->AddAnimation("idle-2", 28, 41)->AddAnimation("spikes-out", 42, 49)->PlayAnim("idle-1")->SetScale(1.5)->SetAnimationDuration(100);

}

void Engine::Lesson06_ObjectPool::SpawnObjects()
{
	//Find Die object to reuse for spawning
	int spawnCount = 0;
	for (Turtle* o : objects) {
		if (spawnCount == numObjectPerSpawn) {
			break;
		}
		if (o->IsDie()) {
			// Set state to spawn
			o->SetSpawn();
			// Random spawn position
			int min = 0;
			int max = (int) (setting->screenWidth - o->GetWidth());
			float x = (float)(rand() % (max - min + 1) + min);
			float y = setting->screenHeight + o->GetHeight();
			o->SetPosition(x, y);
			spawnCount++;
		}
	}
}



