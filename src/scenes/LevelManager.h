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
	const Level& getLevel() const { return _levels[_currentLevel]; }
	void loadNextLevel();
};