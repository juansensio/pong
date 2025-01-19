#include <fstream>
#include <iostream>

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
		int goalCount = std::stoi(line);
		auto level = Level(levelId, goalCount);
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
	if (_currentLevel >= _numLevels - 1) {
		GameEngine::instance().changeScene<SceneMenu>("menu");
	}
	_currentLevel++;
	_levels[_currentLevel].init();
}