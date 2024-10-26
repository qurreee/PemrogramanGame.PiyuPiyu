#ifndef LESSON03_ANIMATION_H
#define LESSON03_ANIMATION_H

#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"

namespace Engine {
	class Lesson03_Animation :public Engine::Game
	{
	public:
		Lesson03_Animation(Setting* setting);
		~Lesson03_Animation();
		virtual void Init();
		virtual void Update();
		virtual void Render();
	private:
		Engine::Texture* texture = NULL;
		Engine::Sprite* sprite = NULL;
	};
}

#endif

