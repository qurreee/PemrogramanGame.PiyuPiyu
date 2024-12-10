#include "PPPlayer.h"
#include <iostream>
#include <random>

Engine::PPPlayer::PPPlayer(Texture* texture, int playerNum, int initialHealth, int initialDamage)
    : playerTexture(texture), playerNum(playerNum), health(initialHealth), damage(initialDamage)
{
}

Engine::PPPlayer::~PPPlayer()
{
    for (PPProjectile* p : inUseBullets) {
        delete p;
    }
}

void Engine::PPPlayer::Init(Game* game)
{
    // Inisialisasi sprite
    playerSprite = new Sprite(playerTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
    playerSprite->SetNumXFrames(4)->SetNumYFrames(20)->SetScale(5)->SetAnimationDuration(60);
    playerSprite->SetBoundingBoxSize(playerSprite->GetScaleWidth(), playerSprite->GetScaleHeight());

    // Menentukan animasi berdasarkan playerNum
    if (playerNum == 0)
    {
        playerSprite->AddAnimation("idle", 0, 3)
            ->AddAnimation("gas" , 4,7)
            ->AddAnimation("l", 8, 11)
            ->AddAnimation("r", 12, 15);
    }
    else if (playerNum == 1)
    {
        playerSprite->AddAnimation("idle", 16, 19)
            ->AddAnimation("gas", 20, 23)
            ->AddAnimation("l", 24, 27)
            ->AddAnimation("r", 28, 31);
    }
    else if (playerNum == 2)
    {
        playerSprite->AddAnimation("idle", 32, 35)
            ->AddAnimation("gas", 36, 39)
            ->AddAnimation("l", 40, 43)
            ->AddAnimation("r", 44, 47);
    }
    else if (playerNum == 3)
    {
        playerSprite->AddAnimation("idle", 48, 51)
            ->AddAnimation("gas", 52, 55)
            ->AddAnimation("l", 56, 59)
            ->AddAnimation("r", 60, 63);
    }
    else if (playerNum == 4)
    {
        playerSprite->AddAnimation("idle", 64, 67)
            ->AddAnimation("gas", 68, 71)
            ->AddAnimation("l", 72, 75)
            ->AddAnimation("r", 76, 79);
    }

    playerSprite->PlayAnim("idle");

    //bullet
    bulletTexture = new Texture("PiyuPiyuAssets/shipprojectile.png");
    int bulletNum = 50;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribIndex(0, 5);
    int bltIndex = distribIndex(gen);
    for (int i = 0; i < bulletNum; i++) {
        Engine::PPProjectile* p = new PPProjectile(bulletTexture,Type::player);
        p->Init(game,bltIndex);
        readyBullets.push_back(p);
    }
}

void Engine::PPPlayer::Update(float deltaTime)
{
	playerSprite->Update(deltaTime);
    timeInterval += deltaTime;
    if (poweredUp)
    {
        powerUpDura += deltaTime;
    }
    if (powerUpDura >= 20000.0f)
    {
        poweredUp = false;
        this->damage = 1;
    }
    if (doubleScore) {
        doubleScoreDura += deltaTime;
    }
    if (doubleScoreDura >= 20000)
    {
        doubleScore = false;
        this->scoreModifier = 1;
    }

    for (PPProjectile* p : inUseBullets) {
        // setting peluru hilang
        if (p->GetPosition().y > 1000) { 
            readyBullets.push_back(p);
            inUseBullets.erase(remove(inUseBullets.begin(), inUseBullets.end(), p), inUseBullets.end());
        }
        p->Update(deltaTime);
    }
}

void Engine::PPPlayer::Draw()
{
    for (PPProjectile* p : inUseBullets) {
        p->Draw();
    }
	playerSprite->Draw();
}

Engine::Sprite* Engine::PPPlayer::getSprite()
{
    return playerSprite;
}

vec2 Engine::PPPlayer::GetPosition()
{
	return playerSprite->GetPosition();
}

void Engine::PPPlayer::SetPosition(float x, float y)
{
	playerSprite->SetPosition(x, y);
}

Engine::BoundingBox* Engine::PPPlayer::GetBoundingBox()
{
	return playerSprite->GetBoundingBox();
}

int Engine::PPPlayer::GetDamage() const
{
    return this->damage;
}

int Engine::PPPlayer::GetHealth() const
{
    return this->health;
}

void Engine::PPPlayer::Move(const std::string& direction, float deltaTime)
{
    // Mendapatkan posisi saat ini
    float x = playerSprite->GetPosition().x;
    float y = playerSprite->GetPosition().y;
    float ratio = (deltaTime / 16.7f);

    if (direction == "r") // Gerak ke kanan
    {
        x += speed * ratio; // Tambahkan ke posisi x
    }
    else if (direction == "l") // Gerak ke kiri
    {
        x -= speed * ratio; // Kurangi dari posisi x
    }
    else if (direction == "u") // Gerak ke atas
    {
        y += speed * ratio; 
    }
    else if (direction == "d") // Gerak ke bawah
    {
        y -= speed * ratio; // Tambahkan ke posisi y
    }

    playerSprite->SetPosition(x, y);
}

void Engine::PPPlayer::Shoot()
{
    if (timeInterval >= 300) { 
        if (readyBullets.empty()) {
            return; // Tidak ada peluru yang siap
        }
        PPProjectile* p = readyBullets.back();
        readyBullets.pop_back();
        p->SetPosition(playerSprite->GetPosition().x, playerSprite->GetPosition().y + playerSprite->GetScaleHeight() * 0.2f); 
        p->yVelocity = 10; // Ke atas
        inUseBullets.push_back(p);
        timeInterval = 0; // Reset interval waktu
    }
}

void Engine::PPPlayer::SetDamage(int damage)
{
	this->damage = damage;
}

void Engine::PPPlayer::SetHealth(int health)
{
    const int maxHealth = 5;
    this->health = health;

    if (health > maxHealth) {
        this->health = maxHealth;
    }
    else if (health < 0) {
        this->health = 0; // Prevent health from going below 0
    }
}

bool Engine::PPPlayer::IsDie() const
{
    return this->health == 0;
}

int Engine::PPPlayer::GetModifier() const
{
    return scoreModifier;
}

int Engine::PPPlayer::GetCombo() const 
{
    return combo;
}

void Engine::PPPlayer::AddCombo()
{
    combo += 1;
}

void Engine::PPPlayer::ResetCombo()
{
    combo = 0;
}

void Engine::PPPlayer::TriggerPowerUp()
{
    if (!this->poweredUp)
    {
        this->poweredUp = true;
        this->damage += 2;
        this->powerUpDura = 0;
    }
}

bool Engine::PPPlayer::PowerUp() const
{
    return poweredUp;
}

void Engine::PPPlayer::TriggerDoubleScore()
{
    if (!this->doubleScore)
    {
        this->doubleScore = true;
        this->scoreModifier = 2;
        this->doubleScoreDura = 0;
    }
}

void Engine::PPPlayer::GetDamaged(int dmg)
{
    const int maxHealth = 5;
    this->health -= dmg;

    if (health > maxHealth) {
        this->health = maxHealth;
    }
    else if (health < 0) {
        this->health = 0; // Prevent health from going below 0
    }
}

bool Engine::PPPlayer::BulletHit(PPEnemy* enemy)
{
    for (auto it = inUseBullets.begin(); it != inUseBullets.end(); ++it) {
        PPProjectile* p = *it;

        if (enemy->GetBoundingBox()->CollideWith(p->GetBoundingBox()))
        {
            readyBullets.push_back(p);
            it = inUseBullets.erase(it);
            return true;
        }
    }
    return false;
}