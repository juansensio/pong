#pragma once

#include "raylib.h"
#include <vector>

enum ShopItemTier {
	COMMON = 0,
	RARE = 1,
	EPIC = 2,
	LEGENDARY = 3
};

enum ShopItemUpgrade {
	HEALTH = 0,
	SPEED = 1,
	SIZE = 2,
};

enum ShopItemDowngrade {
	NONE = 0,
	ENEMY_SPEED = 1,
	ENEMY_SIZE = 2,
};

// for each tier, we have a vector of probas and ranges (min and max)
using ShopItemModifiers = std::vector<std::tuple<std::vector<float>, std::vector<std::vector<int>>>>;

class ShopItem {
	ShopItemTier 		_tier;
	Vector2 			_position;
	int					_width;
	int					_height;
	Color				_color;
	std::string			_tierText;
	ShopItemUpgrade		_upgrade;
	std::string			_upgradeText;
	ShopItemDowngrade 	_downgrade;
	std::string			_downgradeText;
	int				_upgradeValue;
	int				_downgradeValue;
public:
	ShopItem(Vector2 position, int width, int height, const std::vector<float>& probasTiers, const ShopItemModifiers& upgrades, const ShopItemModifiers& downgrades);
	~ShopItem() = default;

	void render();
	void apply();
	const Vector2& getPosition() const { return _position; }
	const int& getWidth() const { return _width; }
	const int& getHeight() const { return _height; }
};