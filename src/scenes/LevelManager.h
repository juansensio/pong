#pragma once

#include "Level.h"
#include <vector>

class LevelManager {
	std::string 			_filename = "levels.txt";
	int 					_currentLevel;
	int 					_numLevels;
	std::vector<Level> 		_levels;

public:
	LevelManager() = default;
	~LevelManager() = default;

	void init();
	void loadLevelsFile();

	const int getCurrentLevel() const { return _currentLevel; }
	const int getNumLevels() const { return _numLevels; }
	const Level& getLevel() const { return _levels[_currentLevel]; }
	void loadNextLevel();
	const std::vector<Level>& getLevels() const { return _levels; }
};