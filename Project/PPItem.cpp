#include "PPItem.h"

Engine::PPItem::PPItem(int typeInt, PPPlayer* p1, PPPlayer* p2) : typeInt(typeInt), P1(p1), P2(p2)
{
}

void Engine::PPItem::Init(Game* game)
{
	itemTexture = new Texture("PiyuPiyuAssets/PowerUpCoin.png");
	itemSprite = new Sprite(itemTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());

	itemSprite->SetNumXFrames(6)->SetNumYFrames(4)->SetAnimationDuration(160)->SetScale(5);

	switch (typeInt) {
	case 1:
		type = ItemType::DamageBoost;
		itemSprite->AddAnimation("default", 0,5);
		break;
	case 2:
		type = ItemType::Heal;
		itemSprite->AddAnimation("default", 6, 11);
		break;
	case 3:
		type = ItemType::Revive;
		itemSprite->AddAnimation("default", 12, 17);
		break;
	case 4:
		type = ItemType::DoubleScore;
		itemSprite->AddAnimation("default", 18, 23);
		break;
	}
	itemSprite->PlayAnim("default");

}


void Engine::PPItem::Update(float deltaTime)
{
	itemSprite->Update(deltaTime);
}

void Engine::PPItem::Draw()
{
	itemSprite->Draw();
}

void Engine::PPItem::SetPosition(int x, int y)
{
	itemSprite->SetPosition(x, y);
}

Engine::BoundingBox* Engine::PPItem::GetBoundingBox()
{
	return itemSprite->GetBoundingBox();
}

Engine::ItemType Engine::PPItem::GetType()
{
	return type;
}

bool Engine::PPItem::CanSpawn()
{
	if (type == Engine::ItemType::Revive) {
		if (gameData.IsMultiplayer()) {
			if (P1->IsDie() || P2->IsDie())
			{
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		return true;
	}
}

void Engine::PPItem::GiveEffect(PPPlayer* p)
{
	switch (type)
	{
	case Engine::ItemType::DamageBoost:
		p->TriggerPowerUp();
		break;
	case Engine::ItemType::Heal:
		p->SetHealth(p->GetHealth() + 2);
		break;
	case Engine::ItemType::Revive:
		if (p == P1) {
			P2->SetHealth(2);
		}
		else if (p == P2) {
			P1->SetHealth(2);
		}
		break;
	case Engine::ItemType::DoubleScore:
		p->TriggerDoubleScore();
		break;
	}
}
