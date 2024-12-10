#pragma once

#include "Sprite.h"
#include "Texture.h"
#include "Game.h"
#include "BoundingBox.h"

#include "PPProjectile.h"
#include "PPPlayer.h"

namespace Engine
{
	enum class EnemyType
	{
		xs,
		s,
		m,
		l,
		xl		
	};
	class PPEnemy
	{
	public:
		PPEnemy(Texture* texture, int enemyNum);
		~PPEnemy();

		void Init(Game* game);
		void Update(float deltaTime);
		void Draw();

		Sprite* GetSprite();
		vec2 GetPosition();
		void SetPosition(float x, float y);
		BoundingBox* GetBoundingBox();
		int GetHealth() const;
		int GetDamage() const;
		int GetBulletNum() const;
		EnemyType GetType() const;

		void Move(float deltaTime);
		bool CanShoot() const;
		void SetDamage(int damage);
		void SetHealth(int health);
		int GetScoreValue();

		void GetDamaged(int dmg);

		//void BulletHit(PPPlayer* player);
		float timeInterval = 4000;
	private:
		vector<PPProjectile*> readyBullets;
		vector<PPProjectile*> inUseBullets;
		Engine::Texture* enemyTexture = NULL;
		Engine::Sprite* enemySprite = NULL;
		Engine::Texture* bulletTexture = NULL;

		EnemyType type = EnemyType::xs;
		int health = 0;
		int damage = 0;
		float speed = 0;
		int bulletNum = 0;
		
		int scoreValue = 0;
	};
}

