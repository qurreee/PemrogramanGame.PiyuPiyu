#ifndef CACTUS_H
#define CACTUS_H

#include "Sprite.h"
#include "Game.h"
#include "BoundingBox.h"


namespace Engine {
	class Cactus {
	public:
        Cactus(Sprite* sprite);
        ~Cactus();
        void Update(float deltaTime);
        void Draw();
        vec2 GetPosition();
        void SetPosition(float x, float y);
        Sprite* GetSprite();
        BoundingBox* GetBoundingBox();

        float xVelocity = 7.0f;
  
    private:
        Engine::Sprite* sprite;

    protected:
        Game* game = nullptr;
	};

}


#endif // !CACTUS_H
