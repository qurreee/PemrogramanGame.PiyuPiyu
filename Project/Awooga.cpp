#include "Awooga.h"

Engine::Awooga::Awooga(Setting* setting) : Engine::Game(setting)
{
	setting->windowTitle = "Dino Game";
}

Engine::Awooga::~Awooga()
{
	delete sprite;
	delete texture;
	delete cactus;
}

void Engine::Awooga::Init()
{
	SetBackgroundColor(255, 255, 0);
	texture = new Texture("cactus.png");
	sprite = new Sprite(texture, defaultSpriteShader, defaultQuad);

	cactus = new Cactus(sprite);
}

void Engine::Awooga::Update()
{
	cactus->Update(GetGameTime());
}

void Engine::Awooga::Render()
{
	cactus->Draw();
}