#pragma once
#include "Game.h"
#include "Setting.h"


#include "PPMenu.h"
#include "PPGame.h"
#include "PPScoreBoard.h"



namespace Engine {
	class PPManager :public Engine::Game
	{
	public:
		PPManager(Setting* setting);
		~PPManager();
		virtual void Init();
		virtual void Update();
		virtual void Render();
	};
}


