#include "PPGame.h"
#include <iostream>
#include <random>
#include <string>
#include <fstream>

Engine::PPGame::PPGame() : gameData(Engine::PPGameData::GetInstance())
{

}

Engine::PPGame::~PPGame()
{
	
}

void Engine::PPGame::Init()
{
	BackgroundInit();

	playerTexture = new Texture("PiyuPiyuAssets/playership.png");
	//P1
	int skin1 = gameData.GetP1Skin();
	std::cout << "skin: " << gameData.GetP1Skin() << std::endl;
	P1 = new PPPlayer(playerTexture, skin1);
	P1->Init(game);
	P1->SetPosition((game->GetSettings()->screenWidth) / 2 - P1->getSprite()->GetScaleWidth(), 150);
	activePlayers.push_back(P1); 

	std::cout << "IsMultiplayer: " << gameData.IsMultiplayer() << std::endl;
	//P2
	if (gameData.IsMultiplayer())
	{
		std::cout << "multiplayer" << std::endl;
		P1->SetPosition((game->GetSettings()->screenWidth / 2) - 200 - P1->getSprite()->GetScaleWidth(), 150);

		int skin2 = gameData.GetP2Skin();
		P2 = new PPPlayer(playerTexture, skin2);
		P2->Init(game);
		P2->SetPosition((game->GetSettings()->screenWidth / 2) + 200, 150);
		activePlayers.push_back(P2);
		std::cout << "multiplayer" << std::endl;
	}

	//commoninput
	game->GetInputManager()
		->AddInputMapping("exit", SDLK_ESCAPE);
	//inputmanager p1
	game->GetInputManager()
		->AddInputMapping("u1", SDLK_w)
		->AddInputMapping("d1", SDLK_s)
		->AddInputMapping("r1", SDLK_d)
		->AddInputMapping("l1", SDLK_a)
		->AddInputMapping("atk1", SDLK_e);
	//p2
	game->GetInputManager()
		->AddInputMapping("u2", SDLK_i)
		->AddInputMapping("d2", SDLK_k)
		->AddInputMapping("r2", SDLK_l)
		->AddInputMapping("l2", SDLK_j)
		->AddInputMapping("atk2", SDLK_o);

	ReadEnemyWave();
	InitEnemy();
	InitItems();
	
	bgMusic = new Music("PiyuPiyuAssets/beksongem.ogg");
	bgMusic->SetVolume(40)->Play(true);

	shootSound = new Sound("PiyuPiyuAssets/piyu.wav");
	shootSound->SetVolume(50);

	explodeSound1 = new Sound("PiyuPiyuAssets/duar.wav");
	explodeSound1->SetVolume(50);
	explodeSound2 = new Sound("PiyuPiyuAssets/duar2.wav");
	explodeSound2->SetVolume(50);
}

void Engine::PPGame::Update()
{
	//wavedelay
	waveDelay += game->GetGameTime();

	//aes
	defBg->Update(game->GetGameTime());
	P1hs->Update(game->GetGameTime());
	if (gameData.IsMultiplayer())
	{
		P2hs->Update(game->GetGameTime());
	}

	//update background harus di Update()
	gameplayBg->Update(game->GetGameTime());
	frame->Update(game->GetGameTime());

	//update player
	for (auto player : activePlayers)
	{
		player->Update(game->GetGameTime());
	}

	//enemyUpdate
	DeployEnemy();
	EnemyShoot();
	for (auto it = deployEnemy.begin(); it != deployEnemy.end();) {
		PPEnemy* enemy = *it;
		enemy->Update(game->GetGameTime());

		if (enemy->GetPosition().y <= -30) {
			deadEnemy.push_back(enemy); 
			it = deployEnemy.erase(it); 
		}
		else {
			++it; 
		}

		for (auto pIt = inUseBullets.begin(); pIt != inUseBullets.end();) {
			PPProjectile* p = *pIt;

			if (p->GetPosition().y < -5) {
				enemyBulletsMap[enemy].push_back(p);
				pIt = inUseBullets.erase(pIt); 
			}
			else {
				++pIt; // Hanya increment jika tidak menghapus
			}
		}
	}

	//damage enemy
	for (auto p : inUseBullets)
	{
		p->Update(game->GetGameTime());
	}
	DamagingEnemy();
	DamagingPlayer();
	
	//input exit
	if (game->GetInputManager()->IsKeyPressed("exit"))
	{
		bgMusic->Stop();
		std::cout << gameData.GetP1Score() << std::endl;
		ScreenManager::GetInstance(game)->SetCurrentScreen("gameover");
	}

	oldPos1 = P1->GetPosition();
	if (gameData.IsMultiplayer())
	{
		oldPos2 = P2->GetPosition();
	}
	
	//input P1
	if (game->GetInputManager()->IsKeyPressed("u1"))
	{
		P1->Move("u", game->GetGameTime());
		P1->getSprite()->PlayAnim("gas");
	}
	if (game->GetInputManager()->IsKeyReleased("u1"))
	{
		P1->getSprite()->PlayAnim("idle");
	}
	if (game->GetInputManager()->IsKeyPressed("d1"))
	{
		P1->Move("d", game->GetGameTime());
	}
	if (game->GetInputManager()->IsKeyPressed("l1"))
	{
		P1->getSprite()->PlayAnim("l");
		P1->Move("l", game->GetGameTime());
	}
	if (game->GetInputManager()->IsKeyPressed("r1"))
	{
		P1->getSprite()->PlayAnim("r");
		P1->Move("r", game->GetGameTime());
	}
	if (game->GetInputManager()->IsKeyReleased("l1") || game->GetInputManager()->IsKeyReleased("r1") ||
		game->GetInputManager()->IsKeyPressed("l1") && game->GetInputManager()->IsKeyPressed("r1"))
	{
		P1->getSprite()->PlayAnim("idle");
	}
	if (game->GetInputManager()->IsKeyPressed("atk1"))
	{
		P1->Shoot();
		
	}
	if (!P1->GetBoundingBox()->CollideWith(gameplayBg->GetBoundingBox()))
	{
		float x = oldPos1.x;
		float y = oldPos1.y;
		P1->SetPosition(x, y);
		std::cout << P1->GetPosition().x << " | "<< P1->GetPosition().y  << std::endl;
	}
	

	//input P2
	if (gameData.IsMultiplayer())
	{
		if (game->GetInputManager()->IsKeyPressed("u2"))
		{
			P2->Move("u", game->GetGameTime());
			P2->getSprite()->PlayAnim("gas");
		}
		if (game->GetInputManager()->IsKeyReleased("u2"))
		{
			P2->getSprite()->PlayAnim("idle");
		}
		if (game->GetInputManager()->IsKeyPressed("d2"))
		{
			P2->Move("d", game->GetGameTime());
		}
		if (game->GetInputManager()->IsKeyPressed("l2"))
		{
			P2->getSprite()->PlayAnim("l");
			P2->Move("l", game->GetGameTime());
		}
		if (game->GetInputManager()->IsKeyPressed("r2"))
		{
			P2->getSprite()->PlayAnim("r");
			P2->Move("r", game->GetGameTime());
		}
		if (game->GetInputManager()->IsKeyReleased("l2") || game->GetInputManager()->IsKeyReleased("r2") ||
			game->GetInputManager()->IsKeyPressed("l2") && game->GetInputManager()->IsKeyPressed("r2"))
		{
			P2->getSprite()->PlayAnim("idle");
		}
		if (game->GetInputManager()->IsKeyPressed("atk2"))
		{
			P2->Shoot();
		}
		if (!P2->GetBoundingBox()->CollideWith(gameplayBg->GetBoundingBox()))
		{
			float x = oldPos2.x;
			float y = oldPos2.y;
			P2->SetPosition(x, y);
		}
	}
	
	//Health UI
	int P1Health = P1->GetHealth();
	if (P1->PowerUp())
	{
		Sprite* p1 = P1hs;
		switch (P1Health)
		{
		case 0:
			p1->PlayAnim("B0");
			break;
		case 1:
			p1->PlayAnim("B1");
			break;
		case 2:
			p1->PlayAnim("B2");
			break;
		case 3:
			p1->PlayAnim("B3");
			break;
		case 4:
			p1->PlayAnim("B4");
			break;
		case 5:
			p1->PlayAnim("B5");
			break;
		}
	}
	else {
		Sprite* p1 = P1hs;
		switch (P1Health)
		{
		case 0:
			p1->PlayAnim("0");
			break;
		case 1:
			p1->PlayAnim("1");
			break;
		case 2:
			p1->PlayAnim("2");
			break;
		case 3:
			p1->PlayAnim("3");
			break;
		case 4:
			p1->PlayAnim("4");
			break;
		case 5:
			p1->PlayAnim("5");
			break;
		}
	}

	int P2Health;
	if (gameData.IsMultiplayer())
	{
		P2Health = P2->GetHealth();
		if (P2->PowerUp())
		{
			Sprite* p1 = P2hs;
			switch (P2Health)
			{
			case 0:
				p1->PlayAnim("B0");
				break;
			case 1:
				p1->PlayAnim("B1");
				break;
			case 2:
				p1->PlayAnim("B2");
				break;
			case 3:
				p1->PlayAnim("B3");
				break;
			case 4:
				p1->PlayAnim("B4");
				break;
			case 5:
				p1->PlayAnim("B5");
				break;
			}
		}
		else {
			Sprite* p1 = P2hs;
			switch (P2Health)
			{
			case 0:
				p1->PlayAnim("0");
				break;
			case 1:
				p1->PlayAnim("1");
				break;
			case 2:
				p1->PlayAnim("2");
				break;
			case 3:
				p1->PlayAnim("3");
				break;
			case 4:
				p1->PlayAnim("4");
				break;
			case 5:
				p1->PlayAnim("5");
				break;
			}
		}
	}
	
	//dead player
	for (auto it = activePlayers.begin(); it != activePlayers.end();)
	{
		if ((*it)->IsDie()) // Assuming GetHealth() returns the health of the player
		{
			explodeSound2->Play(false);
			deadPlayers.push_back(*it); // Move to dead players
			it = activePlayers.erase(it); // Remove from active players
		}
		else
		{
			++it; // Only increment if not erased
		}
	}
	//revive
	for (auto it = deadPlayers.begin(); it != deadPlayers.end();)
	{
		if ((*it)->GetHealth() > 0) // Assuming GetHealth() returns the health of the player
		{
			(*it)->SetPosition((game->GetSettings()->screenWidth) / 2 - P1->getSprite()->GetScaleWidth(), 150);
			activePlayers.push_back(*it); // Move to dead players
			it = deadPlayers.erase(it); // Remove from active players
		}
		else
		{
			++it; // Only increment if not erased
		}
	}

	itemSpawnTime += game->GetGameTime();
	//std::cerr << itemSpawnTime << std::endl;
	SpawnItem();
	CollectItem();
	for (auto i : deployItems) {
		i->Update(game->GetGameTime());
	}

	//parallax
	parallax1->Update(game->GetGameTime());
	parallax2->Update(game->GetGameTime());
	ScrollParallax();

	if (P1->IsDie() && (!gameData.IsMultiplayer() || P2->IsDie())) {
		ScreenManager::GetInstance(game)->SetCurrentScreen("gameover");
	}

}

void Engine::PPGame::Draw()
{
	defBg->Draw();
	gameplayBg->Draw();
	parallax2->Draw();
	parallax1->Draw();

	for (PPEnemy* enemy : deployEnemy) {
		enemy->Draw(); 
	}
	for (auto p : inUseBullets)
	{
		p->Draw();
	}

	for (auto i : deployItems)
	{
		i->Draw();
	}
		
	for (auto player : activePlayers)
	{
		player->Draw();
	}

	P1hs->Draw();
	P1ScoreText->Draw();
	if (gameData.IsMultiplayer())
	{
		P2hs->Draw();
		P2ScoreText->Draw();
	}


	frame->Draw();
	
}

void Engine::PPGame::CleanUp()
{
	for (PPPlayer* player : activePlayers) {
		if (player) {
			deadPlayers.push_back(player); // Pindahkan ke deadPlayers
		}
	}
	activePlayers.clear(); // Bersihkan daftar pemain aktif
	std::cerr << "Active players moved to deadPlayers." << std::endl;

	deadPlayers.clear(); // Bersihkan daftar pemain mati
	std::cerr << "Dead players cleared." << std::endl;
	
	
	currentRow = 0;
	waveDelay = 8000;
	std::cout << "enemies cleared up" << std::endl;

	for (auto it = inUseBullets.begin(); it != inUseBullets.end(); ) {
		PPProjectile* p = *it;
		delete p; // Hapus objek
		it = inUseBullets.erase(it); // Hapus elemen dari vektor dan lanjutkan ke elemen berikutnya
	}
	std::cerr << "All in-use bullets deleted and cleared." << std::endl;

	deployEnemy.clear();
	deadEnemy.clear();
	readyEnemy.clear();
	enemyPositions.clear();
	enemyBulletsMap.clear();
	projectileToEnemyMap.clear();

	for (auto it = deployItems.begin(); it != deployItems.end();) {
		PPItem* item = *it;
		delete item;
		it = deployItems.erase(it);
	}
	itemSpawnTime = 4500;
}

void Engine::PPGame::BackgroundInit()
{
	//aestethic
	defBgT = new Texture("PiyuPiyuAssets/PiyuPiyuBg.png");
	defBg = new Sprite(defBgT, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	defBg->SetScale(10);

	healthscoreT = new Texture("PiyuPiyuAssets/P1HealthScore.png");
	P1hs = new Sprite(healthscoreT, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	P1hs->SetNumXFrames(6)->SetNumYFrames(4)->SetScale(10)->SetPosition(40, game->GetSettings()->screenHeight / 3)
		->AddAnimation("B5", 0, 0)
		->AddAnimation("B4", 1, 1)
		->AddAnimation("B3", 2, 2)
		->AddAnimation("B2", 3, 3)
		->AddAnimation("B1", 4, 4)
		->AddAnimation("B0", 5, 5)
		->AddAnimation("5", 6, 6)
		->AddAnimation("4", 7, 7)
		->AddAnimation("3", 8, 8)
		->AddAnimation("2", 9, 9)
		->AddAnimation("1", 10, 10)
		->AddAnimation("0", 11, 11)
		->PlayAnim("0"); 


	P2hs = new Sprite(healthscoreT, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	P2hs->SetNumXFrames(6)->SetNumYFrames(4)->SetScale(10)->SetPosition(game->GetSettings()->screenWidth - 225 - P2hs->GetScaleWidth(), game->GetSettings()->screenHeight / 3)
		->AddAnimation("B5", 12, 12)
		->AddAnimation("B4", 13, 13)
		->AddAnimation("B3", 14, 14)
		->AddAnimation("B2", 15, 15)
		->AddAnimation("B1", 16, 16)
		->AddAnimation("B0", 17, 17)
		->AddAnimation("5", 18, 18)
		->AddAnimation("4", 19, 19)
		->AddAnimation("3", 20, 20)
		->AddAnimation("2", 21, 21)
		->AddAnimation("1", 22, 22)
		->AddAnimation("0", 23, 23)
		->PlayAnim("0");

	P1ScoreText = (new Text("8-bit Arcade In.ttf", 100, game->GetDefaultTextShader()))->SetPosition(P1hs->GetPosition().x +40, P1hs->GetPosition().y + 40);
	P2ScoreText = (new Text("8-bit Arcade In.ttf", 100, game->GetDefaultTextShader()))->SetPosition(P2hs->GetPosition().x + 40, P2hs->GetPosition().y + 40);

	P1ScoreText->SetText("0");
	P2ScoreText->SetText("0");

	//gameplayarea
	gameplayBgT = new Texture("PiyuPiyuAssets/bg.png");
	gameplayBg = new Sprite(gameplayBgT, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	gameplayBg->AddAnimation("bg", 0, 0)->PlayAnim("bg")->SetScale(10);
	//boundingboxgameplayarea
	gameplayBg->SetBoundingBoxSize((gameplayBg->GetScaleWidth() / 3) + 100, gameplayBg->GetScaleHeight() - 160);

	parallaxT = new Texture("PiyuPiyuAssets/parallaxbg.png");
	parallax1 = new Sprite(parallaxT, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	parallax1->SetScale(2);
	parallax2 = new Sprite(parallaxT, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	parallax2->SetScale(2);
	parallax2->SetPosition(0,parallax1->GetScaleHeight());

	frameT = new Texture("PiyuPiyuAssets/frame.png");
	frame = new Sprite(frameT, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	frame->AddAnimation("frame", 0, 0)->PlayAnim("bg")->SetScale(10);
}

void Engine::PPGame::ScrollParallax()
{
	vec2 oldPos1 = parallax1->GetPosition();
	float y1 = oldPos1.y;
	float ratio = (game->GetGameTime() / 16.7f);
	float speed = 0.3f;

	float newY1 = y1 - (speed * ratio);

	parallax1->SetPosition(0, newY1);

	if (newY1 < -parallax1->GetScaleHeight()) {
		parallax1->SetPosition(0, parallax2->GetScaleHeight());
	}

	vec2 oldPos2 = parallax2->GetPosition();
	float y2 = oldPos2.y;

	float newY2 = y2 - (speed * ratio);

	parallax2->SetPosition(0, newY2);

	if (newY2 < -parallax2->GetScaleHeight()) {
		parallax2->SetPosition(0, parallax1->GetScaleHeight());
	}
}

void Engine::PPGame::ReadEnemyWave()
{
	int random = GetRandomNumber(1, 3);
	string filename = "PiyuPiyuAssets/EnemyWave" + std::to_string(random)+ ".txt";
	std::ifstream file(filename);
	std::string line;


	while (std::getline(file, line))
	{
		std::vector<int> row;
		for (char c : line)
		{
			row.push_back(c - '0');
		}
		enemyPositions.push_back(row);
	}
}

void Engine::PPGame::InitEnemy()
{
	float areaWidth = 772.0f / 5;  // Lebar tiap area
	
	//enemy
	enemyTexture = new Texture("PiyuPiyuAssets/enemySprite.png");
	bulletTexture = new Texture("PiyuPiyuAssets/shipprojectile.png");
	for (size_t i = 0; i < enemyPositions.size(); ++i)
	{
		std::vector<Engine::PPEnemy*> enemyRow;
		for (size_t j = 0; j < enemyPositions[i].size(); ++j)
		{
			int posArea = j;
			int enemyType = enemyPositions[i][j];
			if (enemyType > 0)
			{
				int rand = GetRandomNumber(-15, 15);

				Engine::PPEnemy* e = new PPEnemy(enemyTexture, enemyType);
				e->Init(game);
				//550 sampai 1322
				float spawnX = (550.0f + (posArea + 0.5f) * areaWidth) + rand ;
				e->SetPosition(spawnX, game->GetSettings()->screenHeight + 20);
				enemyRow.push_back(e);
				
				//init projcetile
				
				int bltIndex = GetRandomNumber(0,5);
				int bulletNum = e->GetBulletNum();
				enemyBulletsMap[e] = std::vector<PPProjectile*>();
				for (int i = 0; i < bulletNum; i++) {
					Engine::PPProjectile* p = new PPProjectile(bulletTexture, Type::enemy);
					p->Init(game, bltIndex);
					enemyBulletsMap[e].push_back(p);
					projectileToEnemyMap[p] = e;
				}
			}
		}
		readyEnemy.push_back(enemyRow);
	}
}

void Engine::PPGame::DeployEnemy()
{
	if (waveDelay >= 9000 && currentRow < readyEnemy.size())
	{
		for (PPEnemy* e : readyEnemy[currentRow])
		{
			deployEnemy.push_back(e);
		}
		currentRow++;
		waveDelay = 0;
	}
}

void Engine::PPGame::EnemyShoot()
{
	for (auto e : deployEnemy)
	{
		if (e->CanShoot())
		{
			if (e->timeInterval >= 3200) {
				auto it = enemyBulletsMap.find(e);
				if (it != enemyBulletsMap.end() && !it->second.empty())
				{
					PPProjectile* p = it->second.back();
					it->second.pop_back();
					
					float x;
					if (e->GetType() == EnemyType::xl)
					{
						p->SetPosition(e->GetPosition().x + (e->GetSprite()->GetScaleWidth() / 4), e->GetSprite()->GetPosition().y);
						shootSound->Play(false);
					}
					else
					{
						p->SetPosition(e->GetPosition().x, e->GetPosition().y);
						shootSound->Play(false);
					}
					
					inUseBullets.push_back(p);
					e->timeInterval = 0;

				}
			}
		}
	}
}

void Engine::PPGame::DamagingEnemy()
{
	for (auto it = deployEnemy.begin(); it != deployEnemy.end();)
	{
		PPEnemy* e = *it;

		// Iterate over active players
		for (auto player : activePlayers)
		{
			if (player->BulletHit(e)) // Check if the player's bullet hits the enemy
			{
				e->GetDamaged(player->GetDamage()); // Damage the enemy based on the player's damage
				player->AddCombo();


				if (e->GetHealth() <= 0) // Check if the enemy is dead
				{
					deadEnemy.push_back(e); // Move the enemy to dead list
					it = deployEnemy.erase(it); // Remove the enemy from deploy list
					explodeSound1->Play(false);
					if (player == P1) {
						int score = (e->GetScoreValue() * player->GetModifier()) + (player->GetCombo() * player->GetModifier() * 10);
						gameData.SetP1Score(gameData.GetP1Score() + score);
						P1ScoreText->SetText(std::to_string(gameData.GetP1Score()));
					}
					else
					{
						int score = (e->GetScoreValue() * player->GetModifier()) + (player->GetCombo() * player->GetModifier() * 10);
						gameData.SetP2Score(gameData.GetP2Score() + score);
						P2ScoreText->SetText(std::to_string(gameData.GetP2Score()));
					}
					std::cout << gameData.GetP1Score() << "|" << gameData.GetP2Score() << std::endl;

					break; // Break out of the player loop since the enemy is already dead
				}
			}
		}
		if (it != deployEnemy.end())
		{
			++it;
		}
	}
}

void Engine::PPGame::DamagingPlayer()
{
	for (auto player : activePlayers)
	{
		//menabrak musuh
		for (auto it = deployEnemy.begin(); it != deployEnemy.end();)
		{
			PPEnemy* e = *it;

			if (e->GetBoundingBox()->CollideWith(player->GetBoundingBox()))
			{
				player->GetDamaged(1); // Damage the player
				player->ResetCombo();
				it = deployEnemy.erase(it); 
				continue; // Move to the next enemy
			}
			else
			{
				++it; // Increment iterator if no collision
			}
		}

		//check collision player and bullets
		for (auto bulletIt = inUseBullets.begin(); bulletIt != inUseBullets.end();)
		{
			PPProjectile* p = *bulletIt;

			if (player->GetBoundingBox()->CollideWith(p->GetBoundingBox()))
			{
				auto it = projectileToEnemyMap.find(p);//identifikasi musuh yang nembak

				int damage = (it != projectileToEnemyMap.end() ? it->second->GetDamage() : 1);
				player->GetDamaged(damage);
				player->ResetCombo();
				bulletIt = inUseBullets.erase(bulletIt);
			}
			else
			{
				++bulletIt;
			}
		}

	}
}

void Engine::PPGame::InitItems()
{	 
	for (int i = 1; i <= 4; i++) {
		for (int j = 0; j < 5; j++) { // 10 item per jenis
			PPItem* item = new PPItem(i, P1, P2);
			item->Init(game);
			readyItems.push_back(item);
		}
	}

}

void Engine::PPGame::SpawnItem()
{
	if (itemSpawnTime >= 5000) {
		if (!readyItems.empty()) {
			// Ambil indeks acak dari readyItems
			int randomIndex = GetRandomNumber(0, 19);
			PPItem* item = readyItems[randomIndex];

			// Periksa apakah item valid
			if (item != nullptr) {
				float spawnX = GetRandomNumber(563 + 5, 1324 - 5);
				float spawnY = GetRandomNumber(21 + 10, 994 - 10);
				item->SetPosition(spawnX, spawnY);

				// Pindahkan item ke deployItems jika bisa spawn
				if (item->CanSpawn()) {
					deployItems.push_back(item);
					readyItems.erase(readyItems.begin() + randomIndex);  // Hapus item yang sudah dipindah
				}
			}
		}
		itemSpawnTime = 0;
	}
}

void Engine::PPGame::CollectItem()
{
	for (auto p : activePlayers)
	{
		for (auto it = deployItems.begin(); it != deployItems.end();)
		{
			PPItem* item = *it;
			if (p->GetBoundingBox()->CollideWith(item->GetBoundingBox()))
			{
				item->GiveEffect(p);  
				readyItems.push_back(item);
				it = deployItems.erase(it);  
			}
			else
			{
				++it;
			}
		}
	}
}

int Engine::PPGame::GetRandomNumber(int min, int max) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min, max);
	return dis(gen);
}

