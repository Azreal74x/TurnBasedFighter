#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class ScoreManager {

public:

	ScoreManager() {}
	~ScoreManager() {}

	const int GetScore();
	void SetScore(int newScore);

	void LoadHighscores();
	void SaveHighscores();
	void ClearHighscores();      
	void CheckHighscore();

	std::string FormatHighScores() const;

private:

	int m_score = 0;
	int m_highscore = 0;

	std::vector<int> topScores = { 0, 0, 0, 0, 0 }; 
	const std::string filename = "highscores.cmgt"; 
};

