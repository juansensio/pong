#include "ShopItem.h"
#include "../../GameEngine.h"


ShopItem::ShopItem(Vector2 position, int width, int height, const std::vector<float>& probasTiers, const ShopItemModifiers& upgrades, const ShopItemModifiers& downgrades) : _position(position), _width(width), _height(height) {
	// Generate a random float between 0 and 1
	float random = static_cast<float>(GetRandomValue(0, 10000)) / 10000.0f;
	float cumulativeProb = 0.0f;
	// Default to COMMON if something goes wrong
	_tier = COMMON;
	int tier = 0;
	// Sample from the probability distribution
	for (size_t i = 0; i < probasTiers.size(); i++) {
		cumulativeProb += probasTiers[i];
		if (random <= cumulativeProb) {
			tier = i;
			_tier = static_cast<ShopItemTier>(i);
			break;
		}
	}
	// assign a color based on the tier
	switch (_tier) {
		case COMMON:
			_color = GRAY;
			_tierText = "Common";	
			break;
		case RARE:
			_color = BLUE;
			_tierText = "Rare";
			break;
		case EPIC:
			_color = GREEN;
			_tierText = "Epic";
			break;
		case LEGENDARY:
			_color = GOLD;
			_tierText = "Legendary";
			break;
	}
	// generate a random upgrade based on the probas
	random = static_cast<float>(GetRandomValue(0, 10000)) / 10000.0f;
	cumulativeProb = 0.0f;
	std::vector<float> probas = std::get<0>(upgrades[tier]);
	std::vector<std::vector<int>> ranges = std::get<1>(upgrades[tier]);
	for (size_t i = 0; i < probas.size(); i++) {
		cumulativeProb += probas[i];
		if (random <= cumulativeProb) {
			_upgrade = static_cast<ShopItemUpgrade>(i);
			_upgradeValue = GetRandomValue(ranges[i][0], ranges[i][1]);
			switch (_upgrade) {
				case HEALTH:
					_upgradeText = "Health: + " + std::to_string(_upgradeValue);
					break;
				case SPEED:
					_upgradeText = "Speed: + " + std::to_string(_upgradeValue);
					break;
				case SIZE:
					_upgradeText = "Size: + " + std::to_string(_upgradeValue);
					break;
			}
			break;
		}
	}
	// generate a random downgrade based on the probas
	random = static_cast<float>(GetRandomValue(0, 10000)) / 10000.0f;
	cumulativeProb = 0.0f;
	probas = std::get<0>(downgrades[tier]);
	ranges = std::get<1>(downgrades[tier]);
	for (size_t i = 0; i < probas.size(); i++) {
		cumulativeProb += probas[i];
		if (random <= cumulativeProb) {
			_downgrade = static_cast<ShopItemDowngrade>(i);
			_downgradeValue = GetRandomValue(ranges[i][0], ranges[i][1]);
			switch (_downgrade) {
				case ENEMY_SPEED:
					_downgradeText = "Enemy Speed: + " + std::to_string(_downgradeValue);
					break;
				case ENEMY_SIZE:
					_downgradeText = "Enemy Size: + " + std::to_string(_downgradeValue);
					break;
			}
			break;
		}
	}
}

void ShopItem::render() {
	DrawRectangle(_position.x, _position.y, _width, _height, _color);
	int padding = 20;
	DrawText(_tierText.c_str(), _position.x + padding, _position.y + padding, 20, WHITE);
	DrawText(_upgradeText.c_str(), _position.x + padding, _position.y + padding + 30, 20, WHITE);
	if (_downgrade != NONE) {
		DrawText(_downgradeText.c_str(), _position.x + padding, _position.y + padding + 60, 20, WHITE);
	}
}

void ShopItem::apply() {
	auto& player = GameEngine::instance().getCurrentScene()->getPlayer();
	switch (_upgrade) {
		case HEALTH:
			player.increaseHealth((int)_upgradeValue);
			break;
		case SPEED:
			player.increaseSpeed(_upgradeValue);
			player.addUpgrade("Speed", _upgradeValue);
			break;
		case SIZE:
			player.increaseSize(_upgradeValue);
			player.addUpgrade("Size", _upgradeValue);
			break;
	}
	auto& enemies = GameEngine::instance().getCurrentScene()->getEnemy();
	switch (_downgrade) {
		case ENEMY_SPEED:
			enemies.increaseSpeed(_downgradeValue);
			player.addDowngrade("Enemy Speed", _downgradeValue);
			break;
		case ENEMY_SIZE:
			enemies.increaseSize(_downgradeValue);
			player.addDowngrade("Enemy Size", _downgradeValue);
			break;
	}
}
