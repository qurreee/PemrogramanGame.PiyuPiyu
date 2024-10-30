#pragma once

#include "Screen.h"
#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "Button.h"
#include "Text.h"
#include "ScreenManager.h"

namespace Engine {
	class PPMenu: public Engine::Screen
	{
	public:
		PPMenu();
		void Init();
		void Update();
		void Draw();
	private:
		Text* text;
	};
}