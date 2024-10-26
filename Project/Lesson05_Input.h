#ifndef LESSON05_INPUT_H
#define LESSON05_INPUT_H

#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"

namespace Engine {
	class Lesson05_Input :public Engine::Game
	{
	public:
		Lesson05_Input(Setting* setting);
		~Lesson05_Input();
		virtual void Init();
		virtual void Update();
		virtual void Render();
	private:
		Engine::Texture* texture = NULL;
		Engine::Sprite* sprite = NULL;
	};
}

#endif

