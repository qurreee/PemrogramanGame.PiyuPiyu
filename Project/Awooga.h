#ifndef AWOOGA_H
#define AWOOGA_H

#include "Cactus.h"
#include "Texture.h"
#include "Sprite.h"

namespace Engine {
	class Awooga :public Engine::Game
	{
	public:
		Awooga(Setting* setting);
		~Awooga();
		virtual void Init();
		virtual void Update();
		virtual void Render();
	private:
		Engine::Texture* texture = NULL;
		Engine::Sprite* sprite = NULL;
		Engine::Cactus* cactus = NULL;

	};
}

#endif

#pragma once
