#include "PPGameData.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>


Engine::PPGameData& Engine::PPGameData::GetInstance()
{
	static PPGameData instance; 
	return instance;
}

void Engine::PPGameData::TriggerMultiplayer()
{
	if (multiplayerEnabled == true)
	{
		multiplayerEnabled = false;
	}
	else {
		multiplayerEnabled = true;
	}
}

bool Engine::PPGameData::IsMultiplayer() const
{
	return multiplayerEnabled;
}

void Engine::PPGameData::SetP1Score(int score)
{
	this->P1Score = score;
}

int Engine::PPGameData::GetP1Score() const
{
	return this->P1Score;
}

void Engine::PPGameData::SetP2Score(int score)
{
	this->P2Score = score;
}

int Engine::PPGameData::GetP2Score() const
{
	return this->P2Score;
}

void Engine::PPGameData::SetP1Skin(int index)
{
	this->P1Skin = index;
}

int Engine::PPGameData::GetP1Skin()
{
	return this->P1Skin;
}

void Engine::PPGameData::SetP2Skin(int index)
{
	this->P2Skin = index;
}

int Engine::PPGameData::GetP2Skin()
{
	return this->P2Skin;
}

void Engine::PPGameData::Reset()
{
	multiplayerEnabled = false;
	P1Score = 0;
	P2Score = 0;

	P1Skin = 0;
	P2Skin = 1;
	std::cout << "resetted" << std::endl;
}

void Engine::PPGameData::ResetScores()
{
	this->P1Score = 0;
	this->P2Score = 0;
}

void Engine::PPGameData::SaveHighScore(int teamScore, int P1Score, int P2Score)
{
	std::vector<int> teamScores;
	std::ifstream teamFileIn("PiyuPiyuAssets/team_scores.txt");
	int score;
	while (teamFileIn >> score) {
		teamScores.push_back(score);
	}
	teamFileIn.close();

	if (teamScore != 0)
	{
		teamScores.push_back(teamScore);
	}
	std::sort(teamScores.rbegin(), teamScores.rend());

	std::ofstream teamFileOut("PiyuPiyuAssets/team_scores.txt");
	for (const auto& s : teamScores) {
		teamFileOut << s << "\n";
	}
	teamFileOut.close();

	//player
	std::vector<std::pair<std::string, int>> individualScores;
	std::ifstream individualFileIn("PiyuPiyuAssets/individual_scores.txt");
	std::string player;
	while (individualFileIn >> player >> score) {
		individualScores.emplace_back(player, score);
	}
	individualFileIn.close();
	if (P1Score != 0) {
		individualScores.emplace_back("P1", P1Score);
	}
	if (P2Score != 0) {
		individualScores.emplace_back("P2", P2Score);
	}
	std::sort(individualScores.begin(), individualScores.end(), [](const auto& a, const auto& b) {
		return b.second < a.second; // Sort by score descending
		});

	std::ofstream individualFileOut("PiyuPiyuAssets/individual_scores.txt");
	for (const auto& pair : individualScores) {
		individualFileOut << pair.first << " " << pair.second << "\n";
	}
	individualFileOut.close();

	ResetScores();
}

Engine::PPGameData::PPGameData()
	: multiplayerEnabled(false), P1Score(0), P2Score(0), P1Skin(0), P2Skin(1)
{
}

Engine::PPGameData::~PPGameData()
{
}
