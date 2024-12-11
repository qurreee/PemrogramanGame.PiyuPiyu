#pragma once

#include "Screen.h"
#include "Sprite.h"
#include "ScreenManager.h"
#include "Text.h"
#include "Music.h"
#include "Sound.h"

#include "PPGameData.h"
#include "PPPlayer.h"
#include "PPEnemy.h"
#include "PPItem.h"

namespace Engine {
	class PPGame : public Engine::Screen
	{
	public:
		PPGame();
		~PPGame();
		void Init();
		void Update();
		void Draw();
		void CleanUp();

		void BackgroundInit();
		void ScrollParallax();
		
		void ReadEnemyWave();
		void InitEnemy();
		void DeployEnemy();
		void EnemyShoot();

		void DamagingEnemy();
		void DamagingPlayer();

		void InitItems();
		void SpawnItem();
		void CollectItem();

		int GetRandomNumber(int min, int max);

	private:
		Engine::PPGameData& gameData;
		vec2 oldPos1;
		vec2 oldPos2;
		float waveDelay = 8000;
		int currentRow = 0;

		float itemSpawnTime = 4500;
		//P1
		Engine::Texture* playerTexture = NULL;
		Engine::PPPlayer* P1 = NULL;
		Engine::PPPlayer* P2 = NULL;

		std::vector<PPPlayer*> activePlayers; 
		std::vector<PPPlayer*> deadPlayers;

		Engine::Texture* enemyTexture = NULL;

		Engine::Texture* bulletTexture = NULL;
		vector<PPProjectile*> inUseBullets;
		//
		std::unordered_map<PPEnemy*, std::vector<PPProjectile*>> enemyBulletsMap;
		std::unordered_map<PPProjectile*, PPEnemy*> projectileToEnemyMap;

		std::vector<std::vector<PPEnemy*>> readyEnemy;
		vector<PPEnemy*> deployEnemy;
		vector<PPEnemy*> deadEnemy;
		//
		std::vector<std::vector<int>> enemyPositions;
		//
		Engine::Texture* gameplayBgT = NULL;
		Engine::Sprite* gameplayBg = NULL;

		//bg
		Engine::Texture* defBgT = NULL;
		Engine::Sprite* defBg = NULL;
		Engine::Texture* parallaxT = NULL;
		Engine::Sprite* parallax1 = NULL;
		Engine::Sprite* parallax2 = NULL;

		Engine::Texture* frameT = NULL;
		Engine::Sprite* frame = NULL;

		//Health bar and score
		Engine::Texture* healthscoreT = NULL;
		Engine::Sprite* P1hs = NULL;
		Engine::Sprite* P2hs = NULL;

		//scoreText
		Engine::Text* P1ScoreText = NULL;
		Engine::Text* P2ScoreText = NULL;

		//Items
		PPItem* itemEx = NULL;
		std::vector<PPItem*> readyItems;
		std::vector<PPItem*> deployItems;

		//sound
		Music* bgMusic = NULL;
		Sound* shootSound = NULL;

		Sound* explodeSound1 = NULL;
		Sound* explodeSound2 = NULL;
	};
}