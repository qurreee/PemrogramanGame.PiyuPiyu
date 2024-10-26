#ifndef ENEMY_H
#define ENEMY_H

#include "Sprite.h"
#include "BaseCharacter.h"

namespace Engine {
	class Enemy:public Engine::BaseCharacter
	{
	public:
		Enemy(Texture* texture, Shader* shader, Quad* quad);
		~Enemy();
		void Update(float deltaTime);
		void SetTarget(BaseCharacter* target);
		void SetMaxSpeed(float maxSpeed);
		void Move(float deltaTime);
	private:
		vec2 Engine::Enemy::Seek();
		string Engine::Enemy::FacingSprite(vec2 position, vec2 target);
		BaseCharacter *target;
		float maxSpeed;
	};
}
#endif
