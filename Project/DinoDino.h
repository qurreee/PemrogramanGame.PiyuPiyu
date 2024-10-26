#ifndef DINODINO_H
#define DINODINO_H

#include "Screen.h"
#include "Sprite.h"
#include "Turtle.h"
#include "ScreenManager.h"
#include "Text.h"
#include "Cactus.h"

namespace Engine {
	class DinoDino :
		public Engine::Screen
	{
	public:
		DinoDino();
		void Init();
		void Update();
		void Draw();

	private:

		Engine::Texture* texture = NULL;
		Engine::Sprite* sprite = NULL;
		Engine::Texture* cactusT = NULL;
		Engine::Sprite* cactusS = NULL;
		Text* text;

		int score = 0;
		float scoreTime = 0;
		bool scored = false;
		float yVelocity = 0, gravity = 0;
		bool jump = false, debug = false;
		float xVelocity = 0;

		std::vector<Engine::Cactus*> cacti;

		float cactusCount = 0;

		vector<Sprite*> backgrounds, middlegrounds, foregrounds;
		void MoveLayer(vector<Sprite*>& bg, float speed);
		void DrawLayer(vector<Sprite*>& bg);
		void AddToLayer(vector<Sprite*>& bg, string name);
		float offset = 0;
		

		float lastMovementTime;
	};
}

#endif