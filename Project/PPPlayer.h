#pragma once

#include "Sprite.h"
#include "Game.h"
#include "BoundingBox.h"
#include "Texture.h"

#include "PPProjectile.h"
#include "PPEnemy.h"
class PPEnemy;

namespace Engine {
	class PPPlayer
	{
	public:
		PPPlayer(Texture* texture, int playerNum, int initialHealth = 3, int initialDamage = 1);
		~PPPlayer();

		void Init(Game* game);
		void Update(float deltatime);
		void Draw();

		Sprite* getSprite();
		vec2 GetPosition();
		void SetPosition(float x, float y);
		BoundingBox* GetBoundingBox();
		int GetDamage() const;
		int GetHealth() const;
			
		void Move(const std::string& direction, float deltaTime);
		void Shoot();
		void SetDamage(int damage);
		void SetHealth(int health);
		bool IsDie() const;

		//scorestuff
		int GetModifier() const;
		int GetCombo() const;
		void AddCombo();
		void ResetCombo();

		void TriggerPowerUp();
		bool PowerUp() const;

		void TriggerDoubleScore();

		void GetDamaged(int dmg);

		bool BulletHit(PPEnemy* enemy);
		vector<PPProjectile*> readyBullets;
		vector<PPProjectile*> inUseBullets;
		

	private:

		Engine::Texture* playerTexture = NULL;
		Engine::Sprite* playerSprite = NULL;
		Engine::Texture* bulletTexture = NULL;
		int playerNum;
		int health;
		int damage;
		float speed = 7;
		float timeInterval = 0;

		bool poweredUp = false;
		float powerUpDura = 30000.0f;

		int scoreModifier = 1;
		int combo = 0;
		bool doubleScore = false;
		float doubleScoreDura = 15000;
	};
}