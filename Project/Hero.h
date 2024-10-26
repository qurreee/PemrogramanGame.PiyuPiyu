#include "Sprite.h"
#include "BaseCharacter.h"
#include "Input.h"

#ifndef HERO_H
#define HERO_H

namespace Engine {
	class Hero :public Engine::BaseCharacter
	{
	public:
		Hero(Texture* texture, Shader* shader, Quad* quad);
		~Hero();
		void Update(float deltaTime);
		void Move(float deltaTime);
		void Init(Input* inputManager);
	private:
		Input* inputManager;
	};
}
#endif
