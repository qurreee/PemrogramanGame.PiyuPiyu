#ifndef LESSON10_PLATFORM_H
#define LESSON10_PLATFORM_H

#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "Music.h"
#include "Sound.h"
#include "Text.h"
#include <vector>

namespace Engine {
	class Lesson10_Platform :
		public Engine::Game
	{
	public:
		Lesson10_Platform(Setting* setting);
		~Lesson10_Platform();
		virtual void Init();
		virtual void Update();
		virtual void Render();
	private:
		Texture* dotTexture = NULL;
		vector<Sprite*> platforms;
		Sprite* monsterSprite = NULL;
		Sprite* backgroundSprite = NULL;
		Sprite* dotSprite1 = NULL;
		Sprite* dotSprite2 = NULL;
		Sprite* dotSprite3 = NULL;
		Sprite* dotSprite4 = NULL;
		Music* music = NULL;;
		Sound* sound = NULL;
		Text* text = NULL;
		float yVelocity = 0, gravity = 0;
		bool jump = false, debug = false;
	};
}
#endif

