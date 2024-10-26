#include "Lesson03_Animation.h"

Engine::Lesson03_Animation::Lesson03_Animation(Setting* setting) :Engine::Game(setting)
{
	setting->windowTitle = "Animation";
}

Engine::Lesson03_Animation::~Lesson03_Animation()
{
	delete texture;
	delete sprite;
}

void Engine::Lesson03_Animation::Init()
{
	texture = new Texture("turtles.png");
	sprite = new Sprite(texture, defaultSpriteShader, defaultQuad);
	sprite->SetNumXFrames(14)->SetNumYFrames(4)->AddAnimation("hit", 2, 4)->AddAnimation("spikes", 5, 12)->AddAnimation("idle-1", 14, 27)->AddAnimation("idle-2", 28, 41)->AddAnimation("spikes-out", 42, 49)->SetScale(10)->SetAnimationDuration(30)->SetPosition(300, 0)->PlayAnim("idle-1");
	
}

void Engine::Lesson03_Animation::Update()
{
	sprite->Update(GetGameTime());
}

void Engine::Lesson03_Animation::Render()
{
	sprite->Draw();
}

