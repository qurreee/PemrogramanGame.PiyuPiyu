#include "Turtle.h"

Engine::Turtle::Turtle(Sprite* sprite)
{
	this->sprite = sprite;
	state = Engine::TurtleState::DIE;
	groundDur = 0;
	groundTime = 3000;
}

Engine::Turtle::~Turtle()
{

}

void Engine::Turtle::Update(float deltaTime)
{
	if (state == Engine::TurtleState::DIE) {
		return;
	}

	float x = GetX();
	float y = GetY();
	float yVelocity = 0.07f;

	if (Engine::TurtleState::SPAWN == state && y <= 0) {
		state = Engine::TurtleState::GROUND;
	}

	if (state == Engine::TurtleState::GROUND) {
		yVelocity = 0;
		if (groundDur >= groundTime) {
			state = Engine::TurtleState::DIE;
			groundDur = 0;
		}
		groundDur += deltaTime;
	}

	y -= yVelocity * deltaTime;
	sprite->SetPosition(x, y);
	sprite->Update(deltaTime);
}

void Engine::Turtle::Draw()
{
	if (state == Engine::TurtleState::DIE) {
		return;
	}

	sprite->Draw();
}



Engine::Turtle* Engine::Turtle::SetPosition(float x, float y)
{
    sprite->SetPosition(x, y);
	return this;
}

Engine::Turtle* Engine::Turtle::SetSpawn()
{
	this->state = Engine::TurtleState::SPAWN;
	return this;
}

float Engine::Turtle::GetWidth()
{
	return sprite->GetScaleWidth();
}

float Engine::Turtle::GetHeight()
{
	return sprite->GetScaleHeight();
}

bool Engine::Turtle::IsDie()
{
	return Engine::TurtleState::DIE == state;
}

float Engine::Turtle::GetX()
{
	return sprite->GetPosition().x;
}

float Engine::Turtle::GetY()
{
	return sprite->GetPosition().y;
}

