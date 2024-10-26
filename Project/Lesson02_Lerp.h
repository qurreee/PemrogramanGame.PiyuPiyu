#ifndef LESSON02_LERP_H
#define LESSON02_LERP_H

#include "Game.h"
#include "Setting.h"

namespace Engine {
	class Lesson02_Lerp :public Engine::Game
	{
	public:
		Lesson02_Lerp(Setting* setting);
		~Lesson02_Lerp();
		virtual void Init();
		virtual void Update();
		virtual void Render();
	private:
		float color_duration, f;
		int mul, r_y, g_y, b_y, r_p, g_p, b_p;
		int lerp(float a, float b, float f);
	};
}

#endif

