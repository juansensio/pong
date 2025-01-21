#include <fstream>
#include <iostream>
#include <algorithm>

#include "ResultsManager.h"

void ResultsManager::loadScores()
{
	std::ifstream file(_filename);
	if (!file.is_open()) {
		std::ofstream create_file(_filename);
		create_file.close();
		file.open(_filename);
		if (!file.is_open()) {
			std::cerr << "Failed to create and open file: " << _filename << std::endl;
			return;
		}
	}

	std::string line;
	while (std::getline(file, line)) {
		_scores.push_back(std::stof(line));
	}
	file.close();
}

void ResultsManager::addScore(const float& score)
{
	if (_scores.size() < _num_scores) {
		_scores.push_back(score);
	} else {
		_scores.push_back(score);
		std::sort(_scores.begin(), _scores.end());
		_scores.pop_back();
	}
	saveScores();
}

void ResultsManager::saveScores()
{
	std::sort(_scores.begin(), _scores.end());
	std::ofstream file(_filename);
	for (auto& score : _scores) {
		file << score << std::endl;
	}
	file.close();
}