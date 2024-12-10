#pragma once

#include "Screen.h"
#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "Button.h"
#include "Text.h"
#include "ScreenManager.h"
#include "Music.h"

#include "PPGameData.h"

namespace Engine {
	enum class Action
	{
		next,
		prev
	};
	class PPMenu: public Engine::Screen
	{
	public:
		PPMenu();
		~PPMenu();
		void Init();
		void Update();
		void Draw();
		void CleanUp();

		void UpdateSkinSelector(Action action, int player);
	private:
		Engine::PPGameData& gameData;
	
		Engine::Texture* titleT = NULL;
		Engine::Sprite* title = NULL;

		Engine::Texture* P1t = NULL;
		Engine::Sprite* P1 = NULL;

		Engine::Texture* P2t = NULL;
		Engine::Sprite* P2 = NULL;

		Engine::Texture* playBtnT = NULL;
		Engine::Sprite* playBtn = NULL;


		Engine::Texture* tglMulT = NULL;
		Engine::Sprite* tglMul = NULL;

		bool isAtk2Pressed = false;

		bool isR1Pressed = false;
		bool isL1Pressed = false;

		bool isR2Pressed = false;
		bool isL2Pressed = false;

		int ind1 = 0, ind2 = 0;

		Music* bgMusic = NULL;
	};
}