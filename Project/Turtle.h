#ifndef TURTLE_H
#define TURTLE_H

#include "Sprite.h"

namespace Engine {
	enum class TurtleState {
		SPAWN,
		GROUND,
		DIE
	};
	class Turtle
	{
	public:
		Turtle(Sprite* sprite);
		~Turtle();
		void Update(float deltaTime);
		void Draw();
		Turtle* SetPosition(float x, float y);
		Turtle* SetSpawn();
		float GetWidth();
		float GetHeight();
		bool IsDie();
		float GetX();
		float GetY();
	protected:
		Sprite* sprite = NULL;
		TurtleState state;
		float groundDur = 0, groundTime = 0, x = 0, y = 0;
	};

}

#endif