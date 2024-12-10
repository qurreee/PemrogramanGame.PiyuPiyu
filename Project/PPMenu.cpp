#include "PPMenu.h"

Engine::PPMenu::PPMenu() : gameData(Engine::PPGameData::GetInstance())
{

}

Engine::PPMenu::~PPMenu()
{
	// Hapus semua objek Sprite yang dialokasikan
	delete title;
	delete P1;
	delete P2;
	delete playBtn;
	delete tglMul;
	delete titleT;
	delete P1t;
	delete P2t;
	delete playBtnT;
	delete tglMulT;

}

void Engine::PPMenu::Init()
	{
	std::cout << "init menu" << std::endl;
	// texture render title
	titleT = new Texture("PiyuPiyuAssets/piyuLogo.png");
	title = new Sprite(titleT, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	title->SetScale(5)->AddAnimation("bg", 0, 0)->PlayAnim("bg");

	P1t = new Texture("PiyuPiyuAssets/P1Menu.png");
	P1 = new Sprite(P1t, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	P1->SetNumXFrames(5)->SetNumYFrames(1)->SetAnimationDuration(160)
		->AddAnimation("0", 0, 0)
		->AddAnimation("1", 1, 1)
		->AddAnimation("2", 2, 2)
		->AddAnimation("3", 3, 3)
		->AddAnimation("4", 4, 4)
		->PlayAnim(std::to_string(gameData.GetP1Skin()));
	P1->SetScale(5);

	P2t = new Texture("PiyuPiyuAssets/P2Menu.png");
	P2 = new Sprite(P2t, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	P2->SetNumXFrames(5)->SetNumYFrames(1)->SetAnimationDuration(160)
		->AddAnimation("0", 0, 0)
		->AddAnimation("1", 1, 1)
		->AddAnimation("2", 2, 2)
		->AddAnimation("3", 3, 3)
		->AddAnimation("4", 4, 4)
		->PlayAnim(std::to_string(gameData.GetP2Skin()));
	P2->SetScale(5);

	playBtnT = new Texture("PiyuPiyuAssets/playButton.png");
	playBtn = new Sprite(playBtnT, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	playBtn->SetNumXFrames(2)->SetNumYFrames(1)->SetAnimationDuration(160)
		->AddAnimation("default", 0, 0)
		->AddAnimation("pressed", 1, 1)
		->PlayAnim("default");
	playBtn->SetScale(5);

	tglMulT = new Texture("PiyuPiyuAssets/toogleMulti.png");
	tglMul = new Sprite(tglMulT, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	tglMul->SetNumXFrames(2)->SetNumYFrames(1)->AddAnimation("false", 0, 0)->AddAnimation("true", 1,1)->SetAnimationDuration(160);
	tglMul->SetScale(5);
	if (gameData.IsMultiplayer()) {
		tglMul->PlayAnim("true");
	}
	else {
		tglMul->PlayAnim("false");
	}
	//commoninput
	game->GetInputManager()
		->AddInputMapping("exit1", SDLK_BACKSPACE)
		->AddInputMapping("enter", SDLK_RETURN);

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

	bgMusic = new Music("PiyuPiyuAssets/bekson.ogg");
	bgMusic->SetVolume(20)->Play(true);

	std::cout << "initiated menu" << std::endl;
}

void Engine::PPMenu::Update()
{
	title->Update(game->GetGameTime());
	P1->Update(game->GetGameTime());
	P2->Update(game->GetGameTime());
	playBtn->Update(game->GetGameTime());
	tglMul->Update(game->GetGameTime());

	//input
	if (game->GetInputManager()->IsKeyPressed("exit1"))
	{
		game->SetState(Engine::State::EXIT);
	}

	//enter
	if (game->GetInputManager()->IsKeyPressed("enter"))
	{
		bgMusic->Stop();
		playBtn->PlayAnim("pressed");
		Engine::ScreenManager::GetInstance(game)->SetCurrentScreen("ingame");
		std::cout << "play: "  << std::endl;
		//go to screenmanager
	}
	

	//toggle multiplayer
	if (game->GetInputManager()->IsKeyPressed("atk2"))
	{
		if (!isAtk2Pressed) 
		{
			gameData.TriggerMultiplayer();

			if (gameData.IsMultiplayer())
			{
				tglMul->PlayAnim("true");
			}
			else
			{
				tglMul->PlayAnim("false");
			}

			isAtk2Pressed = true; 

			//std::cout << gameData.IsMultiplayer() << std::endl;
		}
	}
	else
	{
		isAtk2Pressed = false; 
	}

	//selector p1
	if (game->GetInputManager()->IsKeyPressed("r1"))
	{
		if (!isR1Pressed)
		{
			isR1Pressed = true; 
			UpdateSkinSelector(Action::next, 1);
		}
	}
	else
	{
		isR1Pressed = false; 
	}
	if (game->GetInputManager()->IsKeyPressed("l1"))
	{
		if (!isL1Pressed)
		{
			isL1Pressed = true; 
			UpdateSkinSelector(Action::prev, 1);
		}
	}
	else
	{
		isL1Pressed = false;
	}

	//selector p2
	if (game->GetInputManager()->IsKeyPressed("r2"))
	{
		if (!isR2Pressed) 
		{
			isR2Pressed = true; 
			UpdateSkinSelector(Action::next, 2);
		}
	}
	else
	{
		isR2Pressed = false;
	}

	if (game->GetInputManager()->IsKeyPressed("l2"))
	{
		if (!isL2Pressed) 
		{
			isL2Pressed = true;
			UpdateSkinSelector(Action::prev, 2);
		}
	}
	else
	{
		isL2Pressed = false;
	}

}

void Engine::PPMenu::Draw()
{
	title->Draw();
	P1->Draw();
	P2->Draw();
	playBtn->Draw();
	tglMul->Draw();
}

void Engine::PPMenu::CleanUp()
{
	std::cout << "menu clean" << std::endl;
}

void Engine::PPMenu::UpdateSkinSelector(Action action, int player)
{
	if (player == 1)
	{
		if (action == Action::next)
		{
			ind1 = (ind1 + 1) % 5; // Menggunakan modulus untuk loop
			gameData.SetP1Skin(ind1);
			std::cout << "skin: " << gameData.GetP1Skin() << std::endl;
		}
		else if (action == Action::prev)
		{
			ind1 = (ind1 - 1 + 5) % 5; // Menggunakan modulus untuk loop
			gameData.SetP1Skin(ind1);
		}

		P1->PlayAnim(std::to_string(ind1));
	}
	else if (player == 2)
	{
		if (action == Action::next)
		{
			ind2 = (ind2 + 1) % 5; // Menggunakan modulus untuk loop
			gameData.SetP2Skin(ind2);
		}
		else if (action == Action::prev)
		{
			ind2 = (ind2 - 1 + 5) % 5; // Menggunakan modulus untuk loop
			gameData.SetP2Skin(ind2);
		}

		P2->PlayAnim(std::to_string(ind2));
	}

}
