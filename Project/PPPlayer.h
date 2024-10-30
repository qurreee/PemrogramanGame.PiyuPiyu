#pragma once

#include "Sprite.h"
#include "Game.h"
#include "BoundingBox.h"
#include "Game.h"
#include "Texture.h"


namespace Engine {
	class PPPlayer
	{
	public:
		PPPlayer(Texture* texture, int initialHealth = 3, int initialDamage = 1);
		PPPlayer(Sprite* sprite, int initialHealth = 3, int initialDamage = 1);
		~PPPlayer();

		void Init(Game* game);
		void Update(float deltatime);
		void Draw();

		vec2 GetPosition();
		void SetPosition(float x, float y);
		BoundingBox* GetBoundingBox();

		void Move();
		void Shoot();
		void SetDamage(int damage);
		void SetHealth(int health);


	private:
		Engine::Texture* playerTexture = NULL;
		Engine::Sprite* playerSprite = NULL;
		int health;
		int damage;
		float speed = 10;

		void logError(const std::string& message);
	};
}


