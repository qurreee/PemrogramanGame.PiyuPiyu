#include "Lesson09_Bullet.h"

Engine::Lesson09_Bullet::Lesson09_Bullet(Setting* setting) :Engine::Game(setting)
{
	setting->windowTitle = "Bullets Spawn";
}

Engine::Lesson09_Bullet::~Lesson09_Bullet()
{
	//delete texture;
	//delete sprite;
}

void Engine::Lesson09_Bullet::Init()
{
	// Add a monster player
	texture = new Texture("monster.png");
	sprite = new Sprite(texture, defaultSpriteShader, defaultQuad);
	sprite->SetNumXFrames(6)->SetNumYFrames(3)->AddAnimation("attack", 13, 14)->AddAnimation("idle", 0, 3)->AddAnimation("run", 6, 11)->PlayAnim("walk")->SetScale(3)->SetAnimationDuration(90);


	// Add bullets
	bulletTexture = new Texture("bullet.png");
	int bulletNum = 50;
	for (int i = 0; i < bulletNum; i++) {
		Sprite* bs = (new Sprite(bulletTexture, defaultSpriteShader, defaultQuad))->SetNumXFrames(1)->SetNumYFrames(1)->SetScale(1);
		readyBullets.push_back(new Bullet(bs));
	}


	// Add input mapping 
	inputManager->AddInputMapping("Run Right", SDLK_RIGHT)->AddInputMapping("Run Left", SDLK_LEFT)->AddInputMapping("Jump", SDLK_UP)->AddInputMapping("Attack", SDLK_x)->AddInputMapping("Run Right", SDL_CONTROLLER_BUTTON_DPAD_RIGHT)->AddInputMapping("Run Left", SDL_CONTROLLER_BUTTON_DPAD_LEFT)->AddInputMapping("Jump", SDL_CONTROLLER_BUTTON_A)->AddInputMapping("Attack", SDL_CONTROLLER_BUTTON_X)->AddInputMapping("Quit", SDLK_ESCAPE)->AddInputMapping("Quit", SDL_CONTROLLER_BUTTON_Y);

	SetBackgroundColor(65, 180, 242);

}

void Engine::Lesson09_Bullet::Update()
{
	timeInterval += GetGameTime();

	// If user press "Quit" key then exit
	if (inputManager->IsKeyReleased("Quit")) {
		state = State::EXIT;
		return;
	}

	sprite->PlayAnim("idle");

	// Move monster sprite using keyboard
	vec2 oldMonsterPos = sprite->GetPosition();
	float x = oldMonsterPos.x, y = oldMonsterPos.y;
	if (inputManager->IsKeyPressed("Run Right")) {
		x += 0.2f * GetGameTime();
		sprite->PlayAnim("run")->SetFlipHorizontal(false);
		toRight = true;
	}

	if (inputManager->IsKeyPressed("Run Left")) {
		x -= 0.2f * GetGameTime();
		sprite->PlayAnim("run")->SetFlipHorizontal(true);
		toRight = false;
	}

	if (inputManager->IsKeyPressed("Jump") && !jump) {
		//Set gravity and yVelocity
		float ratio = (GetGameTime() / 16.7f);
		gravity = 0.1f * ratio;
		yVelocity = 1.6f;
		jump = true;
	}


	if (y > 0) {
		yVelocity -= gravity;
	}
	else if (y < 0) {
		jump = false;
		yVelocity = 0;
		y = 0;
	}


	if (inputManager->IsKeyPressed("Attack")) {
		sprite->PlayAnim("attack");
		SpawnBullets();
	}

	y += yVelocity * GetGameTime();

	// Update monster sprite's position and animation
	sprite->SetPosition(x, y)->Update(GetGameTime());

	for (Bullet* b : inUseBullets) {
		// If bullet off screen then remove a bullet from in-use container, and insert into ready-to-use container
		if (b->GetPosition().x < -b->sprite->GetScaleWidth() || b->GetPosition().x > setting->screenWidth) {
			readyBullets.push_back(b);
			inUseBullets.erase(remove(inUseBullets.begin(), inUseBullets.end(), b), inUseBullets.end());
		}

		b->Update(GetGameTime());
	}

}

void Engine::Lesson09_Bullet::Render()
{
	for (Bullet* b : inUseBullets) {
		b->Draw();
	}

	sprite->Draw();

}

void Engine::Lesson09_Bullet::SpawnBullets()
{
	if (timeInterval >= 150) {
		if (readyBullets.empty()) {
			return;
		}
		Bullet* b = readyBullets.back();
		readyBullets.pop_back();
		b->SetPosition(sprite->GetPosition().x, sprite->GetPosition().y + sprite->GetScaleHeight() * 0.2f);
		if (toRight) {
			b->xVelocity = 0.6f;
		}
		else {
			b->xVelocity = -0.6f;
		}
		inUseBullets.push_back(b);
		timeInterval = 0;

	}

}

