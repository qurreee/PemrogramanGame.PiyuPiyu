#include "LessonAI01_SteeringBehaviors.h"

Engine::LessonAI01_SteeringBehaviors::LessonAI01_SteeringBehaviors(Setting* setting) :Engine::Game(setting)
{
	botSprite = nullptr;
	playerSprite = nullptr;
	texture = nullptr;
	setting->windowTitle = "Steering Behavior : Seek, Flee, Arrival, Pursue, and Evade";
}

Engine::LessonAI01_SteeringBehaviors::~LessonAI01_SteeringBehaviors()
{
}

void Engine::LessonAI01_SteeringBehaviors::Init()
{
	texture = new Texture("s8dchars.png");
	CreatePlayerSprite();
	CreateBotSprite();
	SetBackgroundColor(145, 235, 84);
}

void Engine::LessonAI01_SteeringBehaviors::Update()
{

	if (inputManager->IsKeyPressed("quit")) {
		state = Engine::State::EXIT;
	}

	ControlPlayerSprite();
	ControBotSprite();
}

void Engine::LessonAI01_SteeringBehaviors::Render()
{
	botSprite->Draw();
	playerSprite->Draw();
}

void Engine::LessonAI01_SteeringBehaviors::CreatePlayerSprite()
{
	playerSprite = new Sprite(texture, defaultSpriteShader, defaultQuad);
	playerSprite->SetNumXFrames(96)->SetNumYFrames(1)->AddAnimation("up", 0, 2)
		->AddAnimation("upright", 12, 14)->AddAnimation("right", 24, 26)->AddAnimation("downright", 36, 38)
		->AddAnimation("down", 48, 50)->AddAnimation("downleft", 60, 62)->AddAnimation("left", 72, 74)
		->AddAnimation("upleft", 84, 86)->PlayAnim("down")->SetScale(3)->SetAnimationDuration(90)->SetPosition(0, 0);
	//playerSprite->SetPosition((setting->screenWidth / 2) - 20, setting->screenHeight/2);
	


	inputManager->AddInputMapping("walk-left", SDLK_LEFT)->AddInputMapping("walk-left", SDL_CONTROLLER_BUTTON_DPAD_LEFT)
		->AddInputMapping("walk-left", SDL_CONTROLLER_AXIS_LEFTX)->AddInputMapping("walk-right", SDLK_RIGHT)
		->AddInputMapping("walk-right", SDL_CONTROLLER_BUTTON_DPAD_RIGHT)->AddInputMapping("walk-right", SDL_CONTROLLER_AXIS_RIGHTX)
		->AddInputMapping("walk-up", SDLK_UP)->AddInputMapping("walk-up", SDL_CONTROLLER_BUTTON_DPAD_UP)
		->AddInputMapping("walk-up", SDL_CONTROLLER_AXIS_RIGHTY)->AddInputMapping("walk-down", SDLK_DOWN)
		->AddInputMapping("walk-down", SDL_CONTROLLER_BUTTON_DPAD_DOWN)->AddInputMapping("walk-down", SDL_CONTROLLER_AXIS_LEFTY)\
		->AddInputMapping("quit", SDLK_ESCAPE);

}

void Engine::LessonAI01_SteeringBehaviors::ControlPlayerSprite()
{
	// Get Current Player's Position
	float speed = 0.07f;
	// s = v * t;
	// Control player's movement using keyboard or gamepad
	playerVelocity = vec2(0, 0);
	if (inputManager->IsKeyPressed("walk-up")) {
		playerVelocity += vec2(0.0f, speed);
	}

	if (inputManager->IsKeyPressed("walk-down")) {
		playerVelocity += vec2(0.0f, -speed);
	}

	if (inputManager->IsKeyPressed("walk-right")) {
		playerVelocity += vec2(speed, 0.0f);
	}

	if (inputManager->IsKeyPressed("walk-left")) {
		playerVelocity += vec2(-speed, 0.0f);
	}

	vec2 playerPosition = playerSprite->GetPosition();
	vec2 oldPosition = vec2(playerPosition);
	playerPosition += playerVelocity * GetGameTime();
	// Update new player's position
	playerSprite->SetPosition(playerPosition.x, playerPosition.y)->PlayAnim(FacingSprite(oldPosition, playerPosition))->Update(GetGameTime());
}

void Engine::LessonAI01_SteeringBehaviors::CreateBotSprite()
{
	botSprite = new Sprite(texture, defaultSpriteShader, defaultQuad);
	botSprite->SetNumXFrames(96)->SetNumYFrames(1)->AddAnimation("bot-up", 4, 6)
		->AddAnimation("bot-upright", 16, 18)->AddAnimation("bot-right", 28, 30)
		->AddAnimation("bot-downright", 40, 42)->AddAnimation("bot-down", 52, 54)
		->AddAnimation("bot-downleft", 64, 66)->AddAnimation("bot-left", 76, 78)
		->AddAnimation("bot-upleft", 88, 90)->PlayAnim("bot-down")
		->SetScale(3)->SetAnimationDuration(90)
		->SetPosition(setting->screenWidth / 2.0f, setting->screenHeight / 2.0f);
}

void Engine::LessonAI01_SteeringBehaviors::ControBotSprite()
{
	// Apply steering behavior
	// vec2 steering = Arrival(botSprite->GetPosition(), playerSprite->GetPosition(), botVelocity, 0.15f, 400.0f);
	// vec2 steering = Seek(botSprite->GetPosition(), botVelocity, playerSprite->GetPosition(), 0.06f);
	// vec2 steering = Flee(botSprite->GetPosition(), botVelocity, playerSprite->GetPosition(), 0.06f);
	vec2 steering = Pursue(botSprite->GetPosition(), botVelocity, playerSprite->GetPosition(), playerVelocity, 0.06f);
	// Update Bot Position based on steering behavior
	botVelocity += steering;
	vec2 botPosition = botSprite->GetPosition();
	vec2 oldPosition = vec2(botPosition);
	botPosition += botVelocity * GetGameTime();
	botSprite->SetPosition(botPosition.x, botPosition.y)->PlayAnim("bot-" + FacingSprite(oldPosition, botPosition))->Update(GetGameTime());
}

string Engine::LessonAI01_SteeringBehaviors::FacingSprite(vec2 position, vec2 target)
{
	if (target == position) {
		return "";
	}

	vec2 direction = normalize(target - position);

	float angle = degrees(atan2(direction.y, direction.x));
	if (angle < 0) {
		angle += 360;
	}

	float range = 22.5f;

	if (angle >= (0.0f + range) && angle < (45.0f + range)) {
		return "upright";
	}
	else if (angle >= (45.0f + range) && angle < (90.0f + range)) {
		return "up";
	}
	else if (angle >= (90.0f + range) && angle < (135.0f + range)) {
		return "upleft";
	}
	else if (angle >= (135.0f + range) && angle < (180.0f + range)) {
		return "left";
	}
	else if (angle >= (180.0f + range) && angle < (235.5f + range)) {
		return "downleft";
	}
	else if (angle >= (235.5f + range) && angle < (270.0f + range)) {
		return "down";
	}
	else if (angle >= (270.0f + range) && angle < (315.0f + range)) {
		return "downright";
	}
	else {
		return "right";
	}
}

vec2 Engine::LessonAI01_SteeringBehaviors::Seek(vec2 position, vec2 velocity, vec2 target, float maxSpeed) {
	vec2 desiredVelocity = normalize(target - position) * maxSpeed;
	vec2 steering = desiredVelocity - velocity;
	return steering;
}

vec2 Engine::LessonAI01_SteeringBehaviors::Flee(vec2 position, vec2 velocity, vec2 target, float maxSpeed) {
	vec2 desiredVelocity = normalize(position - target) * maxSpeed;
	vec2 steering = desiredVelocity - velocity;
	return steering;
}

vec2 Engine::LessonAI01_SteeringBehaviors::Arrival(vec2 position, vec2 target, vec2 botVelocity, float maxSpeed, float slowRadius) {
	vec2 desiredVelocity = target - position;
	float distance = length(desiredVelocity);

	if (distance < slowRadius) {
		desiredVelocity = normalize(desiredVelocity);
		desiredVelocity = desiredVelocity * maxSpeed * (distance / slowRadius);
	}
	else {
		desiredVelocity = normalize(desiredVelocity);
		desiredVelocity = desiredVelocity * maxSpeed;
	}

	vec2 steering = desiredVelocity - botVelocity;
	return steering;
}

vec2 Engine::LessonAI01_SteeringBehaviors::Pursue(vec2 position, vec2 velocity, vec2 targetPosition, vec2 targetVelocity, float maxSpeed) {
	float distance = length(targetPosition - position);
	float T = distance / maxSpeed;
	float maxPredictionTime = 0.5f;
	if (maxSpeed <= distance / maxPredictionTime) {
		T = maxPredictionTime;
	}
	vec2 targetFuturePos = targetPosition + targetVelocity * T;
	return Seek(position, botVelocity, targetFuturePos, maxSpeed);
}

