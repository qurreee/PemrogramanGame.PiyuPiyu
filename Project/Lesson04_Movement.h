#ifndef LESSON04_MOVEMENT_H
#define LESSON04_MOVEMENT_H

#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"

namespace Engine {
	class Lesson04_Movement :public Engine::Game
	{
	public:
		Lesson04_Movement(Setting* setting);
		~Lesson04_Movement();
		virtual void Init();
		virtual void Update();
		virtual void Render();
	private:
		Engine::Texture* texture = NULL;
		Engine::Sprite* sprite = NULL;
		float mul = 1;
	};
}

#endif

