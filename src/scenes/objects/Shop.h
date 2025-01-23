#pragma once

#include "raylib.h"

#include "ShopItem.h"
#include "../LevelManager.h"

using ShopItems = std::vector<std::vector<ShopItem>>;

class Shop {

	std::string 				_upgradesFilename = "upgrades.txt";
	std::string 				_downgradesFilename = "downgrades.txt";

	bool 	    				_active = false;
	ShopItems 					_items;
	ShopItemModifiers 			_upgrades;
	ShopItemModifiers 			_downgrades;

public:
	Shop();
	~Shop();

	void init(const LevelManager& levelManager);
	void render();
	void click(Vector2 position);

	bool isActive() { return _active; }
	void enable() { _active = true; }
	void disable() { _active = false; }

	void createItems(int numItems, const std::vector<float>& probasTiers);
};