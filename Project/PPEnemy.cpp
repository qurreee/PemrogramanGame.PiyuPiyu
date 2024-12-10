#include "PPEnemy.h"
#include <random>

Engine::PPEnemy::PPEnemy(Texture* texture, int enemyNum)
{
	this->enemyTexture = texture;
	switch (enemyNum)
	{
	case 1:
		type = EnemyType::xs;
		this->health = 1;
		this->damage = 1;
		this->scoreValue = 100;
		break;
	case 2:
		type = EnemyType::s;
		this->health = 1;
		this->damage = 1;
		this->scoreValue = 100;
		break;
	case 3:
		type = EnemyType::m;
		this->health = 3;
		this->damage = 1;
		this->scoreValue = 300;
		break;
	case 4:
		type = EnemyType::l;
		this->health = 3;
		this->damage = 1;
		this->scoreValue = 300;
		break;
	case 5:
		type = EnemyType::xl;
		this->health = 10;
		this->damage = 2;
		this->scoreValue = 500;
		break;
	}
}

Engine::PPEnemy::~PPEnemy()
{
	
}

void Engine::PPEnemy::Init(Game* game)
{
	enemySprite = new Sprite(enemyTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	enemySprite->SetNumXFrames(6)->SetNumYFrames(10)->SetScale(5)->SetAnimationDuration(60)->SetBoundingBoxSize(enemySprite->GetScaleWidth() * 0.5f, enemySprite->GetScaleHeight() * 0.5f - 10);
	
	std::random_device rd;
	std::mt19937 gen(rd());
	std::array<int, 5> valuesXsSmall = { 0, 6, 12, 18 };
	std::array<int, 5> valuesXsMedium = { 24, 30 };
	std::array<int, 6> valuesXsLarge = { 9, 10, 11, 12, 13, 14 };

	switch (type)
	{
	case Engine::EnemyType::xs:
	case Engine::EnemyType::s:
	{
		std::uniform_int_distribution<> distribY(0, valuesXsSmall.size() - 1);
		int random_index = distribY(gen);
		int yIndex = valuesXsSmall[random_index];
		std::uniform_int_distribution<> distrib(0, 5);
		int index = distrib(gen) + yIndex;
		enemySprite->AddAnimation("idle", index, index);
		enemySprite->SetBoundingBoxSize(enemySprite->GetScaleWidth()*3/4, enemySprite->GetScaleHeight() * 3 / 4);
		bulletNum = 4;
		speed = 0.8;
	}
	break;

	case Engine::EnemyType::m:
	case Engine::EnemyType::l:
	{
		std::uniform_int_distribution<> distribY(0, valuesXsMedium.size() - 1);
		int random_index = distribY(gen);
		int yIndex = valuesXsMedium[random_index];
		std::uniform_int_distribution<> distrib(0, 5);
		int index = distrib(gen) + yIndex;
		enemySprite->AddAnimation("idle", index, index);
		bulletNum = 7;
		speed = 0.6;
	}
	break;

	case Engine::EnemyType::xl:
	{
		std::uniform_int_distribution<> distribY(0, valuesXsLarge.size() - 1);
		int random_index = distribY(gen);
		int yIndex = valuesXsLarge[random_index];
		enemySprite->SetNumXFrames(3)->SetNumYFrames(5);
		enemySprite->AddAnimation("idle", yIndex, yIndex);
		enemySprite->SetBoundingBoxSize(enemySprite->GetScaleWidth(), enemySprite->GetScaleHeight()-10);
		bulletNum = 10;
		speed = 0.3;
	}
	break;
	}
	enemySprite->PlayAnim("idle");	
}

void Engine::PPEnemy::Update(float deltaTime)
{
	enemySprite->Update(deltaTime);
	timeInterval += deltaTime;
	Move(deltaTime);
}

void Engine::PPEnemy::Draw()
{
	for (PPProjectile* p : inUseBullets) {
		p->Draw();
	}
	enemySprite->Draw();
}

Engine::Sprite* Engine::PPEnemy::GetSprite()
{
	return enemySprite;
}

vec2 Engine::PPEnemy::GetPosition()
{
	return enemySprite->GetPosition();
}

void Engine::PPEnemy::SetPosition(float x, float y)
{
	enemySprite->SetPosition(x, y);
}

Engine::BoundingBox* Engine::PPEnemy::GetBoundingBox()
{
	return enemySprite->GetBoundingBox();
}

int Engine::PPEnemy::GetHealth() const
{
	return this->health;
}

int Engine::PPEnemy::GetDamage() const
{
	return this->damage;
}

int Engine::PPEnemy::GetBulletNum() const
{
	return bulletNum;
}

Engine::EnemyType Engine::PPEnemy::GetType() const
{
	return type;
}

void Engine::PPEnemy::Move(float deltaTime)
{
	float x = enemySprite->GetPosition().x;
	float y = enemySprite->GetPosition().y;
	float ratio = (deltaTime / 16.7f);

	if (y > -40)
	{
		y -= speed * ratio;
	}
	enemySprite->SetPosition(x, y);
}

bool Engine::PPEnemy::CanShoot() const
{
	return (type != EnemyType::xs && type != EnemyType::m);
}

void Engine::PPEnemy::SetDamage(int damage)
{
	this->damage = damage;
}

void Engine::PPEnemy::SetHealth(int health)
{
	this->health = health;
}

int Engine::PPEnemy::GetScoreValue()
{
	return scoreValue;
}

void Engine::PPEnemy::GetDamaged(int dmg)
{
	this->health -= dmg;
}

