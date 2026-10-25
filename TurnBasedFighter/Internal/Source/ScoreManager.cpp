#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include "ScoreManager.hpp"

const int ScoreManager::GetScore() {
  return m_score;
}

void ScoreManager::SetScore(int newScore) {
	m_score = newScore;
}

void ScoreManager::CheckHighscore() {
  for (int i = 0; i < 5; i++) {
    if (m_score > topScores[i]) {
      //shift scores
      for (int j = 4; j > i; j--) {
        topScores[j] = topScores[j - 1];
      }
      //add new score
      topScores[i] = m_score;
      break;
    }
  }
}

void ScoreManager::LoadHighscores() {
  std::ifstream inputFile(filename);
  if (!inputFile.is_open()) {
    std::cout << "File " << filename << " does not exist. Created a new one\n";

    //create the highscores file
    std::ofstream outputFile(filename);
    for (int i = 0; i < 5; ++i) {
      outputFile << 0 << "\n";
      topScores.push_back(0);
    }
    outputFile.close();

    //std::cout << "Highscores file created\n";
    return;
  }

  //if file exists already
  topScores.clear();
  int score;
  while (inputFile >> score) {
    topScores.push_back(score);
  }
  inputFile.close();

  //create 5 scores
  while (topScores.size() < 5) {
    topScores.push_back(0);
  }

  //std::cout << "Highscores loaded\n";
}

void ScoreManager::SaveHighscores() {
  std::ofstream outputFile(filename);
  if (!outputFile.is_open()) {
    //std::cerr << "Failed to open " << filename << " for saving!\n";
    return;
  }

  for (int i = 0; i < topScores.size(); ++i) {
    outputFile << topScores[i] << "\n";
  }
  outputFile.close();

  //std::cout << "Highscores saved to file\n";
}

void ScoreManager::ClearHighscores() {
  std::fill(topScores.begin(), topScores.end(), 0); //reset scores to 0

  //overwrite with cleared scores
  std::ofstream outputFile(filename);
  for (int i = 0; i < topScores.size(); ++i) {
    outputFile << topScores[i] << "\n";
  }
  outputFile.close();

  //std::cout << "Highscores cleared\n";
}

std::string ScoreManager::FormatHighScores() const {
  std::ostringstream formatted;
  formatted << "Highscores:\n";
  for (int i = 0; i < topScores.size(); ++i) {
    formatted << topScores[i];
    if (i < topScores.size() - 1) {
      formatted << "\n";
    }
  }
  return formatted.str();
}
