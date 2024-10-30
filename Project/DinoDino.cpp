	#include "DinoDino.h"
#include <random>

	Engine::DinoDino::DinoDino()
	{
		delete texture;
		delete sprite;
		delete cactusT;
		delete cactusS;
		for (auto& cactus : cacti) {
			delete cactus;
		}
		text = NULL;
		score = 0;
		scored = false;


	}

	void Engine::DinoDino::Init()
	{
		game->SetBackgroundColor(255, 255, 255);

		texture = new Texture("Chicken.png");
		//bikin sprite
		sprite = new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
		//bikin animasi sprite
		sprite->SetNumXFrames(6)->SetNumYFrames(2)->AddAnimation("jump", 0, 5)->AddAnimation("walk", 6, 9)->SetScale(4)->SetAnimationDuration(50)->SetPosition(300, -10)->PlayAnim("walk");
		//bounding box sprite
		sprite->SetBoundingBoxSize(sprite->GetScaleWidth() - (16 * sprite->GetScale()), sprite->GetScaleHeight());
	

		game->GetInputManager()->AddInputMapping("jump", SDLK_SPACE)->AddInputMapping("jump", SDLK_UP);
		game->GetInputManager()->AddInputMapping("up1", SDLK_w);
		//text score
		score = 0;
		text = (new Text("8-bit Arcade In.ttf", 100, game->GetDefaultTextShader()))->SetText("score " + std::to_string(score))->SetPosition( 350, game->GetSettings()->screenHeight - 100.0f)->SetColor(0, 0, 0);
		
		

		//init cactuses
		const int numCacti = 3;
		for (int i = 0; i < numCacti; ++i) {
			Engine::Texture* cactusT = new Texture("cactus.png");
			cactusS = new Sprite(cactusT, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
			
			Cactus* cactus = new Cactus(cactusS);
			cacti.push_back(cactus);
		}
		

		//parallax
		for (int i = 0; i <= 4; i++) {
			AddToLayer(backgrounds, "bg0" + to_string(i) + ".png");
		}
		for (int i = 5; i <= 8; i++) {
			AddToLayer(middlegrounds, "bg0" + to_string(i) + ".png");
		}
		for (int i = 9; i <= 9; i++) {
			AddToLayer(foregrounds, "bg0" + to_string(i) + ".png");
		}

		offset = 2;
	}

	void Engine::DinoDino::Update()
	{
		sprite->Update(game->GetGameTime());
		

		for (auto& cactus : cacti) {
			cactus->Update(game->GetGameTime());
			
			if (sprite->GetBoundingBox()->CollideWith(cactus->GetBoundingBox())) {
				ScreenManager::GetInstance(game)->SetCurrentScreen("mainmenu");
				scoreTime = 0;
				score = 0;
				text->SetText("score " + std::to_string(score));
				std::random_device rd;
				std::mt19937 gen(rd());
				std::uniform_int_distribution<> distrib(0, 3200);
				int randomOffset = distrib(gen);
				for (auto& cactus : cacti) {
					cactus->SetPosition(1600 + randomOffset, 0);
				}
				
			}
			
		}


		vec2 oldPos = sprite->GetPosition();
		float x = oldPos.x, y = oldPos.y;
		sprite->SetPosition(x, y);
		//jump
		if (game->GetInputManager()->IsKeyPressed("jump") && !jump)
		{
			float ratio = (game->GetGameTime() / 16.7f);
			gravity = 0.14f * ratio;
			yVelocity = 2.3f;
			jump = true;
			sprite->PlayAnim("jump");
			/*sound->Play(false);*/
		}

		if (y > 0) {
			yVelocity -= gravity;
		}
		else if (y < 0) {
			jump = false;
			yVelocity = 0;
			y = 0;
			sprite->PlayAnim("walk");
		}

		y += yVelocity * game->GetGameTime();
		sprite->SetPosition(x, y);

		float maxX = game->GetSettings()->screenWidth;

		scoreTime += game->GetGameTime();
		if (scoreTime >= 1000.0f)
		{
			score += 5; // Tambahkan skor berdasarkan waktu yang terakumulasi
			scoreTime = 0.0f; // Reset scoreTime
			text->SetText("score " + std::to_string(score));
		}

		MoveLayer(backgrounds, 0.005f);
		MoveLayer(middlegrounds, 0.03f);
		MoveLayer(foregrounds, 0.5f);
	}

	void Engine::DinoDino::Draw()
	{
		DrawLayer(backgrounds);
		DrawLayer(middlegrounds);
		DrawLayer(foregrounds);
		sprite->Draw();
		text->Draw();
		for (Cactus* o : cacti) {
			o->Draw();
		}
		
	}


	void Engine::DinoDino::MoveLayer(vector<Sprite*>& bg, float speed)
	{
		for (Sprite* s : bg) {
			if (s->GetPosition().x < - game->GetSettings()->screenWidth + offset) {
				s->SetPosition(game->GetSettings()->screenWidth + offset - 1, 0);
			}
			s->SetPosition(s->GetPosition().x - speed * game->GetGameTime(), s->GetPosition().y);
			s->Update(game->GetGameTime());
		}
	}

	void Engine::DinoDino::DrawLayer(vector<Sprite*>& bg)
	{
		for (Sprite* s : bg) {
			s->Draw();
		}
	}

	void Engine::DinoDino::AddToLayer(vector<Sprite*>& bg, string name)
	{
		Texture* texture1 = new Texture(name);

		Sprite* s = new Sprite(texture1, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
		s->SetSize(game->GetSettings()->screenWidth + offset, game->GetSettings()->screenHeight);
		bg.push_back(s);

		Sprite* s2 = new Sprite(texture1, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
		s2->SetSize(game->GetSettings()->screenWidth + offset, game->GetSettings()->screenHeight)->SetPosition(game->GetSettings()->screenWidth + offset - 1, 0);
		bg.push_back(s2);
	}

