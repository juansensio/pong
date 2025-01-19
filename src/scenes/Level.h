#pragma once

class Level {

	
	int 			_goalsForNextLevel;
	int 			_levelId;

public:
	Level(int levelId, int goalsForNextLevel) : _levelId(levelId), _goalsForNextLevel(goalsForNextLevel) {}
	~Level() = default;

	void init();

	const int& getGoalsForNextLevel() const { return _goalsForNextLevel; }
};