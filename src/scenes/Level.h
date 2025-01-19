#pragma once

class Level {

	int _goalsForNextLevel;
	int _levelId;

public:
	Level(int levelId) : _levelId(levelId) {}
	~Level() = default;

	void init();


	const int& getGoalsForNextLevel() const { return _goalsForNextLevel; }
};