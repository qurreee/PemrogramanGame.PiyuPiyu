#pragma once

#include "Screen.h"
#include "Sprite.h"
#include "ScreenManager.h"
#include "Music.h"
#include "Text.h"

#include "PPGameData.h"

namespace Engine {
	class PPScoreBoard : public Engine::Screen
	{
	public:
		PPScoreBoard();
		~PPScoreBoard();
		void Init();
		void Update();
		void Draw();
		void CleanUp();

		void ReadScores();
	private:
		Engine::PPGameData& gameData;
		//bg
		Engine::Texture* defBgT = NULL;
		Engine::Sprite* defBg = NULL;

		Engine::Text* p1ScoreText = NULL;
		Engine::Text* p2ScoreText = NULL;
		Engine::Text* teamScoreText = NULL; 
		std::vector<Text*> highScoreTexts;
		std::vector<Text*> pHighScoreTexts;

		Music* bgMusic = NULL;
	};
}


