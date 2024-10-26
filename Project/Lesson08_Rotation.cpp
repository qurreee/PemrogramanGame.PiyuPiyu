#include "Lesson08_Rotation.h"

Engine::Lesson08_Rotation::Lesson08_Rotation(Setting* setting) :Engine::Game(setting)
{
	setting->windowTitle = "Rotation";

}

Engine::Lesson08_Rotation::~Lesson08_Rotation()
{
}

void Engine::Lesson08_Rotation::Init()
{
	texture = new Texture("monster.png");
	sprite = new Sprite(texture, defaultSpriteShader, defaultQuad);
	sprite->SetNumXFrames(6)->SetNumYFrames(3)->AddAnimation("idle", 0, 3)->AddAnimation("walk", 6, 11)->PlayAnim("walk")->SetScale(3)->SetAnimationDuration(10);

	SetBackgroundColor(65, 180, 242);

}

void Engine::Lesson08_Rotation::Update()
{
	float x = sprite->GetPosition().x;
	float y = sprite->GetPosition().y;
	float velocity = 0.2f;
	// s = v * t;
	float maxX = setting->screenWidth - sprite->GetScaleWidth();
	float minX = 0;
	mul *= (x > maxX || x < minX) ? -1 : 1;
	x += velocity * mul * GetGameTime();
	float rotationSpeed = -0.8f;
	degree += mul * rotationSpeed * GetGameTime();
	sprite->SetFlipHorizontal(mul == 1 ? false : true)->SetPosition(x, y)->SetRotation(degree)->Update(GetGameTime());
}

void Engine::Lesson08_Rotation::Render()
{
	sprite->Draw();
}



