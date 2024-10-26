#include "Lesson10_Platform.h"

using namespace Engine;

Lesson10_Platform::Lesson10_Platform(Setting* setting) :Game(setting)
{
	setting->windowTitle = "Platform";
}


Lesson10_Platform::~Lesson10_Platform()
{
	delete dotTexture;
	delete monsterSprite;
	delete dotSprite1;
	delete dotSprite2;
	delete dotSprite3;
	delete dotSprite4;
	delete music;
	delete text;
}

void Lesson10_Platform::Init()
{
	// Generate Platforms
	Texture* platformTexture = new Texture("platform.png");
	vec2 start = vec2(200, 90);
	for (int i = 0; i < 8; i++) {
		Sprite* platformSprite = new Sprite(platformTexture, defaultSpriteShader, defaultQuad);
		platformSprite->SetSize(150, 32)->SetPosition(start.x + i * 210, start.y + i * 60);
		platformSprite->SetBoundingBoxSize(platformSprite->GetScaleWidth() - (16 * platformSprite->GetScale()), platformSprite->GetScaleHeight());
		platforms.push_back(platformSprite);
	}

	//Create background
	Texture* bgTexture = new Texture("bg.png");
	backgroundSprite = (new Sprite(bgTexture, defaultSpriteShader, defaultQuad))->SetSize((float)setting->screenWidth, (float)setting->screenHeight);

	// a monster spritesheet has 6 cols and 2 rows (total frames = 6x2 = 12 frames)
	Texture* monsterTexture = new Texture("monster.png");
	monsterSprite = new Sprite(monsterTexture, defaultSpriteShader, defaultQuad);
	monsterSprite->SetPosition(0, 0)->SetNumXFrames(6)->SetNumYFrames(3)->SetAnimationDuration(70)->SetScale(2.0f)->AddAnimation("attack", 13, 14)->AddAnimation("idle", 0, 3)->AddAnimation("run", 6, 11);
	monsterSprite->SetBoundingBoxSize(monsterSprite->GetScaleWidth() - (16 * monsterSprite->GetScale()),
		monsterSprite->GetScaleHeight() - (4 * monsterSprite->GetScale()));

	// This dot sprite is for visual debugging (to see the actual bounding box) 
	dotTexture = new Texture("dot.png");
	dotSprite1 = new Sprite(dotTexture, defaultSpriteShader, defaultQuad);
	dotSprite2 = new Sprite(dotTexture, defaultSpriteShader, defaultQuad);
	dotSprite3 = new Sprite(dotTexture, defaultSpriteShader, defaultQuad);
	dotSprite4 = new Sprite(dotTexture, defaultSpriteShader, defaultQuad);

	// Add input mapping 
	inputManager->AddInputMapping("Run Right", SDLK_RIGHT)->AddInputMapping("Run Left", SDLK_LEFT)->AddInputMapping("Jump", SDLK_UP)->AddInputMapping("Attack", SDLK_x)->AddInputMapping("Run Right", SDL_CONTROLLER_BUTTON_DPAD_RIGHT)->AddInputMapping("Run Left", SDL_CONTROLLER_BUTTON_DPAD_LEFT)->AddInputMapping("Jump", SDL_CONTROLLER_BUTTON_A)->AddInputMapping("Attack", SDL_CONTROLLER_BUTTON_X)->AddInputMapping("Quit", SDLK_ESCAPE)->AddInputMapping("Quit", SDL_CONTROLLER_BUTTON_Y);

	// Playing music
	music = (new Music("2021-08-16_-_8_Bit_Adventure_-_www.FesliyanStudios.com.ogg"))->SetVolume(40)->Play(true);

	sound = (new Sound("jump.wav"))->SetVolume(100);

	text = new Text("lucon.ttf", 24, defaultTextShader);
	text->SetScale(1.0f)->SetColor(255, 255, 255)->SetPosition(0, setting->screenHeight - (text->GetFontSize() * text->GetScale()));

	//Set the background color
	SetBackgroundColor(102, 195, 242);

	// Set debug
	debug = true;
}

void Lesson10_Platform::Update()
{
	// If user press "Quit" key then exit
	if (inputManager->IsKeyReleased("Quit")) {
		state = State::EXIT;
		return;
	}

	text->SetText(("[FPS = " + to_string(currentFrameRate)) +
		"] Right-Left-Up-X to Move, Jump, Attack");

	monsterSprite->PlayAnim("idle");

	// Move monster sprite using keyboard
	vec2 oldMonsterPos = monsterSprite->GetPosition();
	float x = oldMonsterPos.x, y = oldMonsterPos.y;
	if (inputManager->IsKeyPressed("Run Right")) {
		x += 0.2f * GetGameTime();
		monsterSprite->PlayAnim("run")->SetFlipHorizontal(false);
	}

	if (inputManager->IsKeyPressed("Run Left")) {
		x -= 0.2f * GetGameTime();
		monsterSprite->PlayAnim("run")->SetFlipHorizontal(true);
	}

	monsterSprite->SetPosition(x, y);

	for (Sprite* s : platforms) {
		if (s->GetBoundingBox()->CollideWith(monsterSprite->GetBoundingBox())) {
			//revert x position if collided
			x = oldMonsterPos.x;
			monsterSprite->SetPosition(x, y);
			break;
		}
	}

	if (inputManager->IsKeyPressed("Jump") && !jump) {
		//Set gravity and yVelocity
		float ratio = (GetGameTime() / 16.7f);
		gravity = 0.16f * ratio;
		yVelocity = 1.8f;
		jump = true;
		sound->Play(false);
	}

	if (y > 0) {
		yVelocity -= gravity;
	}
	else if (y < 0) {
		jump = false;
		yVelocity = 0;
		y = 0;
	}


	y += yVelocity * GetGameTime();
	monsterSprite->SetPosition(x, y);

	for (Sprite* s : platforms) {
		if (s->GetBoundingBox()->CollideWith(monsterSprite->GetBoundingBox())) {
			//revert y position if collided
			y = oldMonsterPos.y;
			monsterSprite->SetPosition(x, y);

			//and set jump to false and yVelovity to 0
			yVelocity = 0;
			jump = false;
			break;
		}
	}

	if (inputManager->IsKeyPressed("Attack")) {
		monsterSprite->PlayAnim("attack");
	}

	// Update monster sprite animation
	monsterSprite->Update(GetGameTime());

	if (debug) {
		//Shape for debug
		BoundingBox* bb = monsterSprite->GetBoundingBox();
		dotSprite1->SetPosition(bb->GetVertices()[0].x - (0.5f * dotSprite1->GetScaleWidth()),
			bb->GetVertices()[0].y - (0.5f * dotSprite1->GetScaleHeight()));
		dotSprite2->SetPosition(bb->GetVertices()[1].x - (0.5f * dotSprite2->GetScaleWidth()),
			bb->GetVertices()[1].y - (0.5f * dotSprite2->GetScaleHeight()));
		dotSprite3->SetPosition(bb->GetVertices()[2].x - (0.5f * dotSprite3->GetScaleWidth()),
			bb->GetVertices()[2].y - (0.5f * dotSprite3->GetScaleHeight()));
		dotSprite4->SetPosition(bb->GetVertices()[3].x - (0.5f * dotSprite4->GetScaleWidth()),
			bb->GetVertices()[3].y - (0.5f * dotSprite3->GetScaleHeight()));
	}

}

void Lesson10_Platform::Render()
{
	backgroundSprite->Draw();
	text->Draw();
	for (Sprite* s : platforms) {
		s->Draw();
	}
	monsterSprite->Draw();

	if (debug) {
		dotSprite1->Draw();
		dotSprite2->Draw();
		dotSprite3->Draw();
		dotSprite4->Draw();
	}

}

