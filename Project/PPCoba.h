#pragma once

#include "Screen.h"
#include "Sprite.h"
#include "ScreenManager.h"
#include "Text.h"
#include "Texture.h"


#include "PPPlayer.h"


namespace Engine {
	class PPCoba : public Engine::Game
	{
	public:
		PPCoba(Setting* setting);
		~PPCoba();
		virtual void Init();
		virtual void Update();
		virtual void Render();
	private:

		//P1
		Engine::Texture* PlayerTexture1 = NULL;
		Engine::Sprite* PlayerSprite1 = NULL;
		Engine::PPPlayer* P1 = NULL;

	};
}