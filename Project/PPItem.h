#pragma once

#include "Sprite.h"
#include "Texture.h"
#include "Game.h"
#include "PPPlayer.h"
#include "BoundingBox.h"

#include "PPGameData.h"

namespace Engine {
	enum class ItemType
	{
		DamageBoost,
		Heal,
		Revive,
		DoubleScore,
	};
	class PPItem
	{
	public:
		PPItem(int typeInt, PPPlayer* p1, PPPlayer* p2);
		Texture* itemTexture = NULL;
		Sprite* itemSprite = NULL;

		void Init(Game* game);
		void Update(float deltaTime);
		void Draw();

		void SetPosition(int x, int y);
		BoundingBox* GetBoundingBox();
		ItemType GetType();

		bool CanSpawn();
		void GiveEffect(PPPlayer* p);
	private:
		Engine::PPGameData& gameData = Engine::PPGameData::GetInstance();

		int typeInt;
		ItemType type;

		PPPlayer* P1;
		PPPlayer* P2;
	};
}

