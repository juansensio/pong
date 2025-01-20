#include <fstream>
#include <iostream>
#include <sstream>
#include "LevelManager.h"
#include "../GameEngine.h"
#include "SceneMenu.h"

void LevelManager::loadLevelsFile() {
	std::ifstream file(_filename);
	if (!file.is_open()) {
		std::cerr << "Failed to open file: " << _filename << std::endl;
		return;
	}
	std::string line;
	int levelId = 0;
	while (std::getline(file, line)) {
		// Skip empty lines and comments
		if (line.empty() || line[0] == '#') {
			continue;
		}
		// Read space-separated values from line
		std::istringstream iss(line);
		int goalCount, numItems;
		float proba1, proba2, proba3, proba4;
		iss >> goalCount >> numItems >> proba1 >> proba2 >> proba3 >> proba4;
		auto level = Level(levelId, goalCount, numItems, {proba1, proba2, proba3, proba4});
		_levels.push_back(level);
		levelId++;
	}
	file.close();
}

void LevelManager::init() {
	loadLevelsFile();
	_currentLevel = 0;
	_numLevels = _levels.size();
	for (auto& level : _levels) {
		level.init();
	}
}

void LevelManager::loadNextLevel() {
	_currentLevel++;
	_levels[_currentLevel].init();
}