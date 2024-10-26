#ifndef LESSONAI02_NPCWAVE_H
#define LESSONAI02_NPCWAVE_H

#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "Enemy.h"
#include "Hero.h"
#include <random> 

namespace Engine {
	class LessonAI02_NPCWave :public Engine::Game
	{
	public:
		LessonAI02_NPCWave(Setting* setting);
		~LessonAI02_NPCWave();
		virtual void Init();
		virtual void Update();
		virtual void Render();
	private:
		Texture* texture;
		float spawnTimer;
		vector<Enemy*> enemies;
		Hero* hero;
	};
}
#endif