#include <fstream>
#include <sstream>

#include "Shop.h"
#include "../../GameEngine.h"


Shop::Shop() {}

Shop::~Shop() {}

void Shop::init(const LevelManager& levelManager) {

	// load upgrades files
	std::ifstream upgradesFile(_upgradesFilename);
	if (!upgradesFile.is_open()) {
		std::cerr << "Failed to open file: " << _upgradesFilename << std::endl;
		return;
	}
	std::string line;
	while (std::getline(upgradesFile, line)) {
		// Skip empty lines and comments
		if (line.empty() || line[0] == '#') {
			continue;
		}
		// Read space-separated values from line
		std::istringstream iss(line);
		float proba0, proba1, proba2;
		int rMin0, rMin1, rMin2;
		int rMax0, rMax1, rMax2;
		iss >> proba0 >> rMin0 >> rMax0 >> proba1 >> rMin1 >> rMax1 >> proba2 >> rMin2 >> rMax2;
		std::vector<float> probas = {proba0, proba1, proba2};
		std::vector<std::vector<int>> ranges = {{rMin0, rMax0}, {rMin1, rMax1}, {rMin2, rMax2}};
		_upgrades.push_back(std::make_tuple(probas, ranges));
	}
	upgradesFile.close();


	// load downgrades files
	std::ifstream downgradesFile(_downgradesFilename);
	if (!downgradesFile.is_open()) {
		std::cerr << "Failed to open file: " << _downgradesFilename << std::endl;
		return;
	}
	while (std::getline(downgradesFile, line)) {
		// Skip empty lines and comments
		if (line.empty() || line[0] == '#') {
			continue;
		}
		// Read space-separated values from line
		std::istringstream iss(line);
		float proba0, proba1, proba2;
		int rMin0, rMin1, rMin2;
		int rMax0, rMax1, rMax2;
		iss >> proba0 >> rMin0 >> rMax0 >> proba1 >> rMin1 >> rMax1 >> proba2 >> rMin2 >> rMax2;
		std::vector<float> probas = {proba0, proba1, proba2};
		std::vector<std::vector<int>> ranges = {{rMin0, rMax0}, {rMin1, rMax1}, {rMin2, rMax2}};
		_downgrades.push_back(std::make_tuple(probas, ranges));
	}
	downgradesFile.close();

	// esto peta porque por lo visto si el shop.init se llama en la misma función que el levelManager.init,
	// el levelManager no está inicializado... 
	// auto levelManager = GameEngine::instance().getCurrentScene().getLevelManager();
	for (auto& level : levelManager.getLevels()) {
		createItems(level.getNumItems(), level.getProbasTiers());
	}
}

void Shop::render() {
	int level = GameEngine::instance().getCurrentScene().getLevelManager().getCurrentLevel();
	for (auto& item : _items[level]) {
		item.render();
	}
	std::string text = "Choose an upgrade";
	DrawText(text.c_str(), GetScreenWidth()/2 - MeasureText(text.c_str(), 20)/2, GetScreenHeight()/2 - 140, 20, WHITE);
}

void Shop::click(Vector2 position) {
	int level = GameEngine::instance().getCurrentScene().getLevelManager().getCurrentLevel();
	for (int i = 0; i < _items[level].size(); i++) {
		auto item = _items[level][i];
		if (position.x > item.getPosition().x && position.x < item.getPosition().x + item.getWidth() && position.y > item.getPosition().y && position.y < item.getPosition().y + item.getHeight()) {
			item.apply();
			_active = false;
			GameEngine::instance().getCurrentScene().resume();
		}
	}
}

void Shop::createItems(int numItems, const std::vector<float>& probasTiers) {
	std::vector<ShopItem> items;
	int itemWidth = 200;
	int itemHeight = 200;
	int padding = 20;
	int startX = GetScreenWidth()/2 - (numItems * itemWidth + (numItems - 1) * padding)/2;
	for (int i = 0; i < numItems; i++) {
		Vector2 position = {(float)startX + (i * (itemWidth + padding)), (float)GetScreenHeight()/2 - itemHeight/2};
		items.push_back(ShopItem(position, itemWidth, itemHeight, probasTiers, _upgrades, _downgrades));
	}
	_items.push_back(items);
}