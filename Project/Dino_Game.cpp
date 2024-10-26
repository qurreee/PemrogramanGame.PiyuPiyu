#include "Dino_Game.h"

Engine::Dino_Game::Dino_Game(Setting* setting) :Engine::Game(setting)
{
	setting->windowTitle = "Dino Game";
}

Engine::Dino_Game::~Dino_Game()
{
	delete texture;
	delete sprite;
	delete cactusT;
	delete cactus;
	text = NULL;
	score = 0;
}

void Engine::Dino_Game::Init()
{
	SetBackgroundColor(255, 255, 255);

	texture = new Texture("Chicken.png");
	sprite = new Sprite(texture, defaultSpriteShader, defaultQuad);
	sprite->SetNumXFrames(6)->SetNumYFrames(2)->AddAnimation("jump", 0, 5)->AddAnimation("walk", 6, 9)->SetScale(4)->SetAnimationDuration(50)->SetPosition(300, -10)->PlayAnim("walk");
	sprite->SetBoundingBoxSize(sprite->GetScaleWidth() - (16 * sprite->GetScale()), sprite->GetScaleHeight());

	cactusT = new Texture("cactus.png");
	cactus = new Sprite(cactusT, defaultSpriteShader, defaultQuad);
	cactus->SetScale(4);
	cactus->SetBoundingBoxSize(cactus->GetScaleWidth() - (16 * cactus->GetScale()), cactus->GetScaleHeight());

	//cactus spawn
	cactusCount = 2;

	inputManager->AddInputMapping("jump", SDLK_SPACE)->AddInputMapping("jump", SDLK_UP);


	score = 0;
	text = (new Text("8-bit Arcade In.ttf", 100, GetDefaultTextShader()))->SetText("score " + std::to_string(score))->SetPosition(setting->screenWidth * 0.7f - 500, setting->screenHeight - 100.0f)->SetColor(0, 0, 0);

	
}

void Engine::Dino_Game::Update()
{
	sprite->Update(GetGameTime());
	cactus->Update(GetGameTime());

	vec2 oldPos = sprite->GetPosition();
	float x = oldPos.x, y = oldPos.y;
	sprite->SetPosition(x, y);
	//jump
	if (inputManager->IsKeyPressed("jump") && !jump)
	{
		float ratio = (GetGameTime() / 16.7f);
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

	y += yVelocity * GetGameTime();
	sprite->SetPosition(x, y);

	//cactus move
	
	float cX = cactus->GetPosition().x;
	float cY = cactus->GetPosition().y;
	float xVelocity = 14.0f;

	float maxX = setting->screenWidth;
	float minX = 0;
	
	cactus->SetPosition(maxX+10,0);

	cX -= xVelocity;
	cactus->SetPosition(cX, cY);

	if (cX < 0) {
		cactus->SetPosition(maxX + 10, 0);
		score += 5;
		text->SetText("score " + std::to_string(score));
		xVelocity += 7.0f;
	}
	
	if (sprite->GetBoundingBox()->CollideWith(cactus->GetBoundingBox())) {
		state = State::EXIT;
		return;
	}

	/*text = (new Text("8-bit Arcade In.ttf", 100, game->GetDefaultTextShader()))
		->SetText("Score" + score)->SetPosition(game->GetSettings()->screenWidth * 0.5f - 500, game->GetSettings()->screenHeight - 100.0f)->SetColor(235, 229, 52);*/

	

}

void Engine::Dino_Game::Render()
{
	sprite->Draw();
	cactus->Draw();
	text->Draw();
}

//void Engine::Dino_Game::Spawn() 
//{
//	
//}