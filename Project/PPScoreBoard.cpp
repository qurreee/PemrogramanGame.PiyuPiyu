#include "PPScoreBoard.h"

Engine::PPScoreBoard::PPScoreBoard() : gameData(Engine::PPGameData::GetInstance())
{
}

Engine::PPScoreBoard::~PPScoreBoard()
{
}

void Engine::PPScoreBoard::Init()
{
	defBgT = new Texture("PiyuPiyuAssets/ScorePage.png");
	defBg = new Sprite(defBgT, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	defBg->SetNumXFrames(2)->SetScale(10)->AddAnimation("default", 0, 1)->PlayAnim("default")->SetAnimationDuration(1000);

	p1ScoreText = new Text("8-bit Arcade In.ttf", 100, game->GetDefaultTextShader());
	p1ScoreText->SetText("0")->SetPosition(180, 690);

	p2ScoreText = new Text("8-bit Arcade In.ttf", 100, game->GetDefaultTextShader());
	p2ScoreText->SetText("0")->SetPosition(1460, 690);

	teamScoreText = new Text("8-bit Arcade In.ttf", 100, game->GetDefaultTextShader());
	teamScoreText->SetText("0")->SetPosition(750, 690);


	ReadScores();
	//input
	game->GetInputManager()
		->AddInputMapping("exit2", SDLK_SPACE);

    bgMusic = new Music("PiyuPiyuAssets/beksongemover.ogg");
    bgMusic->SetVolume(100)->Play(true);
}

void Engine::PPScoreBoard::Update()
{
	defBg->Update(game->GetGameTime());

	if (game->GetInputManager()->IsKeyPressed("exit2"))
	{
        bgMusic->Stop();
		Engine::ScreenManager::GetInstance(game)->SetCurrentScreen("menu");
	}

}

void Engine::PPScoreBoard::Draw()
{
	defBg->Draw();
	p1ScoreText->Draw();
	p2ScoreText->Draw();
	teamScoreText->Draw();

	for (auto score : highScoreTexts) {
		score->Draw();
	}
	for (auto score : pHighScoreTexts) {
		score->Draw();
	}
}

void Engine::PPScoreBoard::CleanUp()
{
	highScoreTexts.clear();
	pHighScoreTexts.clear();
}

void Engine::PPScoreBoard::ReadScores()
{
    int p1Score = gameData.GetP1Score();
    int p2Score = gameData.GetP2Score();
    int teamScore = p1Score + p2Score;

    // Set teks skor pemain dan tim
    p1ScoreText->SetText(std::to_string(p1Score));
    p2ScoreText->SetText(std::to_string(p2Score));
    teamScoreText->SetText(std::to_string(teamScore));

    // Simpan skor ke file
    gameData.SaveHighScore(teamScore, p1Score, p2Score);

    // Baca skor tim
    std::vector<int> teamScores;
    std::ifstream teamFileIn("PiyuPiyuAssets/team_scores.txt");
    int score;
    while (teamFileIn >> score) {
        teamScores.push_back(score);
    }
    teamFileIn.close();

    // Tampilkan maksimum 10 skor tim
    int maxTeamScoresToShow = std::min(7, static_cast<int>(teamScores.size()));
    float startY = 440; // Posisi awal Y untuk skor tim
    float gap = 50;     // Jarak antar teks
    for (int i = 0; i < maxTeamScoresToShow; ++i) {
        Text* scoreText = new Text("8-bit Arcade In.ttf", 100, game->GetDefaultTextShader());
        scoreText->SetText(std::to_string(teamScores[i]));
        scoreText->SetPosition(500, startY - (i * gap)); // Atur posisi setiap baris
        highScoreTexts.push_back(scoreText);
    }

    // Baca skor individu
    std::vector<std::pair<std::string, int>> individualScores;
    std::ifstream individualFileIn("PiyuPiyuAssets/individual_scores.txt");
    std::string player;
    while (individualFileIn >> player >> score) {
        individualScores.emplace_back(player, score);
    }
    individualFileIn.close();

    // Tampilkan maksimum 10 skor individu
    int maxIndividualScoresToShow = std::min(7, static_cast<int>(individualScores.size()));
    startY = 440; // Posisi awal Y untuk skor individu
    for (int i = 0; i < maxIndividualScoresToShow; ++i) {
        Text* scoreText = new Text("8-bit Arcade In.ttf", 100, game->GetDefaultTextShader());
        scoreText->SetText(individualScores[i].first + " " + std::to_string(individualScores[i].second));
        scoreText->SetPosition(1230, startY - (i * gap)); // Atur posisi setiap baris
        pHighScoreTexts.push_back(scoreText);
    }
}

