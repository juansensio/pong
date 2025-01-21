#pragma once

#include <string>
#include <vector>
#include <tuple>

#include "Paddle.h"


using Upgrades = std::vector<std::tuple<std::string, int>>;
using Downgrades = std::vector<std::tuple<std::string, int>>;

class Player : public Paddle {
	int 		_score = 0;
	int 		_lives = 3;

	Upgrades 	_upgrades;
	Downgrades 	_downgrades;
public:
	Player() {}
	Player(const std::shared_ptr<Entity>& entity) : Paddle(entity) {}

	void init();
	void update(const float& dt);

	void moveUp();
	void moveDown();
	void stopUp();
	void stopDown();

	void score();
	void die();
	
	const int getLives() const { return _lives; }
	const int getScore() const { return _score; }
	const Upgrades& getUpgrades() const { return _upgrades; }
	const Downgrades& getDowngrades() const { return _downgrades; }

	void increaseHealth(int health) { _lives += health; }

	void addUpgrade(const std::string& upgrade, const int& value) {
		for (auto& [existingUpgrade, existingValue] : _upgrades) {
			if (existingUpgrade == upgrade) {
				existingValue += value;
				return;
			}
		}
		_upgrades.push_back(std::make_tuple(upgrade, value));
	}
	void addDowngrade(const std::string& downgrade, const int& value) { 
		for (auto& [existingDowngrade, existingValue] : _downgrades) {
			if (existingDowngrade == downgrade) {
				existingValue += value;
				return;
			}
		}
		_downgrades.push_back(std::make_tuple(downgrade, value));
	}
};
