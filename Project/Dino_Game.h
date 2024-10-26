	#ifndef DINO_GAME_H
	#define DINO_GAME_H

	#include "Game.h"
	#include "Setting.h"
	#include "Texture.h"
	#include "Sprite.h"
	#include "Text.h"

	namespace Engine {
		class Dino_Game :public Engine::Game
		{
		public:
			Dino_Game(Setting* setting);
			~Dino_Game();
			virtual void Init();
			virtual void Update();
			virtual void Render();
		private:
			Engine::Texture* texture = NULL;
			Engine::Sprite* sprite = NULL;
			Engine::Texture* cactusT = NULL;
			Engine::Sprite* cactus = NULL;
			void Spawn();
			Text* text;
			int score = 0;
			bool scored = false;
			float yVelocity = 0, gravity = 0;
			bool jump = false, debug = false;

			float cactusCount = 0, spawnDuration = 0;
		};
	}

	#endif

	#pragma once
