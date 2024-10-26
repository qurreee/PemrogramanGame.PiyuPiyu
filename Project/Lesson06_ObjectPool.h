#ifndef LESSON06_OBJECTPOOL_H
#define LESSON06_OBJECTPOOL_H

#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "Turtle.h"
#include <vector>

namespace Engine {
	class Lesson06_ObjectPool :public Engine::Game
	{
	public:
		Lesson06_ObjectPool(Setting* setting);
		~Lesson06_ObjectPool();
		virtual void Init();
		virtual void Update();
		virtual void Render();
	private:
		Engine::Texture* texture = NULL;
		Engine::Sprite* CreateSprite();
		void SpawnObjects();
		vector<Engine::Turtle*> objects;
		float spawnDuration = 0, maxSpawnTime = 0, numObjectsInPool = 0, numObjectPerSpawn = 0;
	};
}

#endif

