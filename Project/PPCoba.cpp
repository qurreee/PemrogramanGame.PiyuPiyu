#include "PPCoba.h"
#include <iostream>

Engine::PPCoba::PPCoba(Setting* setting) :Engine::Game(setting)
{
	setting->windowTitle = "Dino Game";
}

Engine::PPCoba::~PPCoba()
{
}

void Engine::PPCoba::Init()
{
	std::cout << "test23" << std::endl;

	//P1 - ganti texture woe
	PlayerTexture1 = new Texture("Chicken.png");
	//bikin sprite
	PlayerSprite1 = new Sprite(PlayerTexture1, defaultSpriteShader, defaultQuad);
	//bikin animasi sprite
	PlayerSprite1->SetNumXFrames(6)->SetNumYFrames(2)->AddAnimation("jump", 0, 5)->AddAnimation("walk", 6, 9)->SetScale(4)->SetAnimationDuration(50)->SetPosition(300, -10)->PlayAnim("walk");
	//bounding box sprite
	//PlayerSprite1->SetBoundingBoxSize(PlayerSprite1->GetScaleWidth() - (16 * PlayerSprite1->GetScale()), PlayerSprite1->GetScaleHeight());
	PlayerSprite1->SetPosition(250, 250);
}

void Engine::PPCoba::Update()
{
	PlayerSprite1->Update(GetGameTime());
}

void Engine::PPCoba::Render()
{
	PlayerSprite1->Draw();
}

