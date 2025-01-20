#pragma once

#include <vector>

class Level {

	
	int 				_goalsForNextLevel;
	int 				_levelId;
	int 				_numItems;
	std::vector<float> 	_probasTiers;

public:
	Level(int levelId, int goalsForNextLevel, int numItems, std::vector<float> probasTiers) : _levelId(levelId), _goalsForNextLevel(goalsForNextLevel), _numItems(numItems), _probasTiers(probasTiers) {}
	~Level() = default;

	void init();

	const int& getGoalsForNextLevel() const { return _goalsForNextLevel; }
	const int& getNumItems() const { return _numItems; }
	const std::vector<float>& getProbasTiers() const { return _probasTiers; }
};