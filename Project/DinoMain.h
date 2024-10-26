#ifndef DINOMAIN_H
#define DINOMAIN_H

#include "Game.h"
#include "Setting.h"
#include "DinoGUI.h"
#include "DinoDino.h"

namespace Engine {
	class DinoMain :public Engine::Game
	{
	public:
		DinoMain(Setting* setting);
		~DinoMain();
		virtual void Init();
		virtual void Update();
		virtual void Render();
	};
}

#endif