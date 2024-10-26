#ifndef SCREEN_H
#define SCREEN_H

#include "Game.h"

namespace Engine {
	class Screen
	{
	public:
		virtual void Init()=0;
		virtual void Update()=0;
		virtual void Draw()=0;
		void SetGame(Game* engine);
	protected:
		Game* game = nullptr;
	};
}
#endif
