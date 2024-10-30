#include "PPGame.h"
#include <iostream>

Engine::PPGame::PPGame()
{

}

Engine::PPGame::~PPGame()
{
	//delete2 disini
	delete P1;
	delete PlayerSprite1;
	delete PlayerTexture1;
}

void Engine::PPGame::Init()
{
	//P1 - ganti texture woe
	PlayerTexture1 = new Texture("Chicken.png");
	P1 = new PPPlayer(PlayerTexture1);
	P1->Init(game);
	P1->SetPosition(350, 250);

	PlayerTexture2 = new Texture("mecha boss run-Sheet.png");
	PlayerSprite1 = new Sprite(PlayerTexture2, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	PlayerSprite1->SetNumXFrames(8)->SetNumYFrames(1)->AddAnimation("Idle", 0, 7)->PlayAnim("idle")->SetAnimationDuration(50)->SetPosition(100,120)->SetScale(1);


	std::cout << "test P1 bisa" << std::endl;

	game->SetBackgroundColor(255, 255, 255);
	
	//inputmanager p1
	game->GetInputManager()
		->AddInputMapping("u1", SDLK_w)
		->AddInputMapping("d1", SDLK_s)
		->AddInputMapping("r1", SDLK_d)
		->AddInputMapping("l1", SDLK_a)
		->AddInputMapping("atk1", SDLK_e);
	//p2
	game->GetInputManager()
		->AddInputMapping("u2", SDLK_i)
		->AddInputMapping("d2", SDLK_k)
		->AddInputMapping("r2", SDLK_l)
		->AddInputMapping("l2", SDLK_j)
		->AddInputMapping("atk2", SDLK_o);
}

void Engine::PPGame::Update()
{
	//update background harus di Update()
	game->SetBackgroundColor(0, 120, 90);

	//update player
	P1->Update(game->GetGameTime());

	PlayerSprite1->Update(game->GetGameTime());
	
}

void Engine::PPGame::Draw()
{
	P1->Draw();
	PlayerSprite1->Draw();
}
