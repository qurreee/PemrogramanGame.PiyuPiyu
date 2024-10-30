#pragma once

#include "Screen.h"
#include "Sprite.h"
#include "ScreenManager.h"
#include "Text.h"


#include "PPPlayer.h"


namespace Engine {
	class PPGame : public Engine::Screen
	{
	public:
		PPGame();
		~PPGame();
		void Init();
		void Update();
		void Draw();
	private:

		//P1
		Engine::Texture* PlayerTexture1 = NULL;
		Engine::Texture* PlayerTexture2 = NULL;
		Engine::Sprite* PlayerSprite1 = NULL;
		Engine::Sprite* PlayerSprite2 = NULL;
		Engine::PPPlayer* P1 = NULL;

	};
}