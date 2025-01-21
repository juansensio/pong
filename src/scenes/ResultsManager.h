#pragma once

#include <vector>

class ResultsManager
{
	std::string 		_filename = "results.txt";
	std::vector<float>  _scores;
	int 				_num_scores = 3;	

public:
	ResultsManager() {}
	~ResultsManager() = default;

	void addScore(const float& score);
	void saveScores();
	void loadScores();
	const std::vector<float>& getScores() const { return _scores; }
};
