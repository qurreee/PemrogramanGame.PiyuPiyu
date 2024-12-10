#pragma once


namespace Engine
{
	class PPGameData
	{
	public:
		static PPGameData& GetInstance();

		PPGameData(const PPGameData&) = delete;
		PPGameData& operator=(const PPGameData&) = delete;

		void TriggerMultiplayer();
		bool IsMultiplayer() const;

		void SetP1Score(int score);
		int GetP1Score() const;

		void SetP2Score(int score);
		int GetP2Score() const;

		void SetP1Skin(int index);
		int GetP1Skin();
		void SetP2Skin(int index);
		int GetP2Skin();

		void Reset();
		void ResetScores();
		void SaveHighScore(int teamScore, int P1Score, int P2Score);
	private:

		PPGameData();
		~PPGameData();

		bool multiplayerEnabled = false;
		int P1Score = 0;
		int P2Score = 0;

		int P1Skin = 0;
		int P2Skin = 1;
	};
}


