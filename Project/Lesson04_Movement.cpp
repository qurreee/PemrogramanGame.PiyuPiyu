#include "Lesson04_Movement.h"

Engine::Lesson04_Movement::Lesson04_Movement(Setting* setting) :Engine::Game(setting)
{
	setting->windowTitle = "Movement";
}

Engine::Lesson04_Movement::~Lesson04_Movement()
{
	//delete texture;
	//delete sprite;
}

void Engine::Lesson04_Movement::Init()
{
	texture = new Texture("monster.png");
	sprite = new Sprite(texture, defaultSpriteShader, defaultQuad);
	sprite->SetNumXFrames(6)->SetNumYFrames(3)->AddAnimation("idle", 0, 3)->AddAnimation("walk", 6, 11)->SetScale(3)->SetAnimationDuration(90)->PlayAnim("walk")->SetWireframe(false);

	SetBackgroundColor(65, 180, 242);
}

void Engine::Lesson04_Movement::Update()
{
	float x = sprite->GetPosition().x;
	float y = sprite->GetPosition().y;
	float velocity = 0.07f;
	// s = v * t;
	float maxX = setting->screenWidth - sprite->GetScaleWidth();
	float minX = 0;
	mul *= (x > maxX || x < minX) ? -1 : 1;
	x += velocity * mul * GetGameTime();
	sprite->SetFlipHorizontal(mul == 1 ? false : true)->SetPosition(x, y)->Update(GetGameTime());
}

void Engine::Lesson04_Movement::Render()
{
	sprite->Draw();
}

