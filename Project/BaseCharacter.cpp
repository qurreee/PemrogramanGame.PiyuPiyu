#include "BaseCharacter.h"

Engine::BaseCharacter::BaseCharacter(Texture* texture, Shader* shader, Quad* quad)
{
	this->sprite = new Sprite(texture, shader, quad);
	state = Engine::CharacterState::ALIVE;
}

Engine::BaseCharacter::~BaseCharacter()
{
	delete sprite;
}

void Engine::BaseCharacter::Update(float deltaTime)
{
	sprite->Update(deltaTime);
}

void Engine::BaseCharacter::Draw()
{
	if (Engine::CharacterState::ALIVE == state) {
		sprite->Draw();
	}
}

void Engine::BaseCharacter::SetPosition(float x, float y)
{
	sprite->SetPosition(x, y);
}

vec2 Engine::BaseCharacter::GetPosition()
{
	return sprite->GetPosition();
}

Engine::Sprite* Engine::BaseCharacter::GetSprite()
{
	return sprite;
}







