#include "LessonAI02_NPCWave.h"


Engine::LessonAI02_NPCWave::LessonAI02_NPCWave(Setting* setting) :Engine::Game(setting)
{
	texture = NULL;
	spawnTimer = 0.0f;
	hero = NULL;
	setting->windowTitle = "Enemy Wave";
}

Engine::LessonAI02_NPCWave::~LessonAI02_NPCWave()
{
	delete hero;
}

void Engine::LessonAI02_NPCWave::Init()
{
	texture = new Texture("s8dchars.png");
	SetBackgroundColor(145, 235, 84);
	hero = new Hero(texture, defaultSpriteShader, defaultQuad);
	hero->Init(inputManager);
	hero->SetPosition(setting->screenWidth / 2.0f - hero->GetSprite()->GetScaleWidth(), setting->screenHeight / 2.0f);
}

void Engine::LessonAI02_NPCWave::Update()
{
	if (inputManager->IsKeyPressed("quit")) {
		state = Engine::State::EXIT;
	}
	// Spawn Enemies
	spawnTimer += GetGameTime();
	if (spawnTimer >= 1000) {
		// create a new enemy
		Enemy* enemy = new Enemy(texture, defaultSpriteShader, defaultQuad);
		// Set random enemy's position
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> disX(0, setting->screenWidth);
		float x = (float)disX(gen);
		uniform_int_distribution<> disY(0, setting->screenHeight);
		float y = (float)disY(gen);
		uniform_int_distribution<> disBorder(0, 3);
		int border = disBorder(gen);
		// 0 = spawn from bottom, 1 = left, 2 = top, 3 = right
		if (0 == border) {
			y = -enemy->GetSprite()->GetScaleHeight();
		}
		else if (1 == border) {
			x = -enemy->GetSprite()->GetScaleWidth();
		}
		else if (2 == border) {
			y = (float)setting->screenHeight;
		}
		else {
			x = (float)setting->screenWidth;
		}
		enemy->SetPosition(x, y);
		enemy->SetMaxSpeed(0.06f);
		enemy->SetTarget(hero);
		enemies.push_back(enemy);
		spawnTimer = 0;
	}

	for (Enemy* e : enemies) {
		e->Update(GetGameTime());
	}

	hero->Update(GetGameTime());

}

void Engine::LessonAI02_NPCWave::Render()
{
	for (Enemy* enemy : enemies) {
		enemy->Draw();
	}
	hero->Draw();
}

