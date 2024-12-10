#pragma once

#include "Sprite.h"
#include "Game.h"
#include "Texture.h"
#include "BoundingBox.h"

namespace Engine {
	enum class Type
	{
		player,
		enemy
	};
	class PPProjectile
	{
	public:
		PPProjectile(Texture* texture, Type type);
		~PPProjectile();



		void Init(Game* game, int index);
		void Update(float deltaTime);
		void Draw();

		void SetPosition(float x, float y);
		vec2 GetPosition();
		BoundingBox* GetBoundingBox();

		float yVelocity = 1.5;
		Texture* texture = NULL;
		Sprite* sprite = NULL;
	private:
		Type type;
	};
}


