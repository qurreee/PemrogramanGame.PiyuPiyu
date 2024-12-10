#include "PPProjectile.h"
#include <random>

Engine::PPProjectile::PPProjectile(Texture* texture, Type type)
{
	this->texture = texture;
	this->type = type;
}

Engine::PPProjectile::~PPProjectile()
{
}

void Engine::PPProjectile::Init(Game* game, int index)
{
	if (type == Type::player)
	{
		sprite = new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
		sprite->SetNumXFrames(6)->SetNumYFrames(1)->SetScale(5)->AddAnimation("a", index, index)->PlayAnim("a")->SetAnimationDuration(40);
	}
	else if (type == Type::enemy)
	{
		sprite = new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
		sprite->SetNumXFrames(6)->SetNumYFrames(1)->SetScale(5)->AddAnimation("a", index, index)->PlayAnim("a")->SetAnimationDuration(40)->SetFlipVertical(true);
		sprite->SetBoundingBoxSize(sprite->GetScaleWidth(), sprite->GetScaleHeight());
	}
}

void Engine::PPProjectile::Update(float deltaTime)
{
	if (type == Type::player)
	{
		sprite->Update(deltaTime);
		float ratio = (deltaTime / 16.7f);
		vec2 position = GetPosition();
		position.y += yVelocity * ratio; // Gerakan ke atas
		SetPosition(position.x, position.y);
	}
	else if (type == Type::enemy)
	{
		sprite->Update(deltaTime);
		float ratio = (deltaTime / 16.7f);
		vec2 position = GetPosition();
		position.y -= yVelocity * ratio; // Gerakan ke atas
		SetPosition(position.x, position.y);
	}
}

void Engine::PPProjectile::Draw()
{
	sprite->Draw();
}

void Engine::PPProjectile::SetPosition(float x, float y)
{
	sprite->SetPosition(x, y);
}

vec2 Engine::PPProjectile::GetPosition()
{
	return sprite->GetPosition();
}

Engine::BoundingBox* Engine::PPProjectile::GetBoundingBox()
{
	return sprite->GetBoundingBox();
}
