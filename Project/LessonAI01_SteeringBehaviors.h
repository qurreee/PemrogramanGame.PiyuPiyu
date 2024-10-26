#ifndef LESSONAI01_STEERINGBEHAVIORS_H
#define LESSONAI01_STEERINGBEHAVIORS_H

#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"

namespace Engine {
	class LessonAI01_SteeringBehaviors :public Engine::Game
	{
	public:
		LessonAI01_SteeringBehaviors(Setting* setting);
		~LessonAI01_SteeringBehaviors();
		virtual void Init();
		virtual void Update();
		virtual void Render();
	private:
		Texture* texture;
		Sprite* playerSprite, * botSprite;
		vec2 botVelocity, playerVelocity;
		string FacingSprite(vec2 position, vec2 target);
		void ControlPlayerSprite();
		void CreatePlayerSprite();
		void ControBotSprite();
		void CreateBotSprite();
		vec2 Seek(vec2 position, vec2 velocity, vec2 target, float maxSpeed);
		vec2 Flee(vec2 position, vec2 velocity, vec2 target, float maxSpeed);
		vec2 Arrival(vec2 position, vec2 target, vec2 botVelocity, float maxSpeed, float slowRadius);
		vec2 Pursue(vec2 position, vec2 velocity, vec2 targetPos, vec2 targetVel, float maxSpeed);
	};
}
#endif