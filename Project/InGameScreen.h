#ifndef INGAMESCREEN_H
#define INGAMESCREEN_H

#include "Screen.h"
#include "Turtle.h"
#include "ScreenManager.h"

namespace Engine {
	class InGameScreen :
		public Engine::Screen
	{
	public:
		InGameScreen();
		void Init();
		void Update();
		void Draw();
	private:
		Engine::Sprite* CreateSprite(Texture* texture);
		void SpawnObjects();
		vector<Turtle*> objects;
		float spawnDuration = 0, maxSpawnTime = 0, numObjectsInPool = 0, numObjectPerSpawn = 0;
	};
}

#endif