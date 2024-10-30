#include "PPPlayer.h"
#include <iostream>

Engine::PPPlayer::PPPlayer(Texture* texture, int initialHealth, int initialDamage) : playerTexture(texture), health(initialHealth), damage(initialDamage) 
{
	playerTexture = texture;
	
}

Engine::PPPlayer::PPPlayer(Sprite* sprite, int initialHealth, int initialDamage) : playerSprite(sprite), health(initialHealth), damage(initialDamage)
{
	//klo pake Constructor ini, Sprite harus uda lengkap pake anim sampai boundingbox
	playerSprite = sprite;
}

Engine::PPPlayer::~PPPlayer()
{
	delete playerSprite;
	delete playerTexture;
}



void Engine::PPPlayer::Init(Game* game)
{
	playerSprite = new Sprite(playerTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	//bikin animasi sprite
	playerSprite->SetNumXFrames(6)->SetNumYFrames(2)->AddAnimation("jump", 0, 5)->AddAnimation("walk", 6, 9)->SetScale(4)->SetAnimationDuration(50)->SetPosition(300, -10)->PlayAnim("walk");
	//bounding box sprite
	playerSprite->SetBoundingBoxSize(playerSprite->GetScaleWidth() - (16 * playerSprite->GetScale()), playerSprite->GetScaleHeight());
}

void Engine::PPPlayer::Update(float deltatime)
{
	playerSprite->Update(deltatime);}

void Engine::PPPlayer::Draw()
{
	playerSprite->Draw();
}

vec2 Engine::PPPlayer::GetPosition()
{
	return playerSprite->GetPosition();
}

void Engine::PPPlayer::SetPosition(float x, float y)
{
	playerSprite->SetPosition(x, y);
}

Engine::BoundingBox* Engine::PPPlayer::GetBoundingBox()
{
	return playerSprite->GetBoundingBox();
}

void Engine::PPPlayer::Move()
{

}

void Engine::PPPlayer::Shoot()
{
}

void Engine::PPPlayer::SetDamage(int damage)
{
	this->damage = damage;
}

void Engine::PPPlayer::SetHealth(int health)
{
	this->health = health;
}

void Engine::PPPlayer::logError(const std::string& message)
{
	std::cerr << "Error: " << message << std::endl;
}

