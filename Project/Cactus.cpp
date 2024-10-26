#include "Cactus.h"
#include <random>

Engine::Cactus::Cactus(Sprite* sprite)
{
    this->sprite = sprite;
    sprite->SetScale(4);
    sprite->SetBoundingBoxSize(sprite->GetScaleWidth() - (16 * sprite->GetScale()), sprite->GetScaleHeight());

    // Inisialisasi posisi random dengan jarak minimal
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 1500);

    int randomOffset = distrib(gen);

    sprite->SetPosition(1590 + randomOffset, 0);  
    xVelocity = 1.0f;
}

Engine::Cactus::~Cactus()
{
   
}

void Engine::Cactus::Update(float deltaTime)
{
    // Update logika kaktus di sini jika diperlukan
    float cX = sprite->GetPosition().x;
    float cY = sprite->GetPosition().y;

    // Gerakkan kaktus ke kiri
     // Kecepatan kaktus
  
    cX -= xVelocity * deltaTime;
    sprite->SetPosition(cX, cY);
   
    

    if (cX < 0)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, 3200); // Jarak minimal 100 pixel

        int randomOffset = distrib(gen);
        cX = 1600 + randomOffset;

        xVelocity += 0.1f;// Respawn cactus at the right side of the screen
    }

    sprite->SetPosition(cX, cY);
}

void Engine::Cactus::Draw()
{
    sprite->Draw(); // Gambar sprite
}

vec2 Engine::Cactus::GetPosition()
{
    return sprite->GetPosition();
}

void Engine::Cactus::SetPosition(float x, float y)
{
    sprite->SetPosition(x, y);
}

Engine::Sprite* Engine::Cactus::GetSprite()
{
    return sprite;
}

Engine::BoundingBox* Engine::Cactus::GetBoundingBox()
{
    return sprite->GetBoundingBox();
}




