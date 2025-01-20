// #include "Shop.h"
#include "../../GameEngine.h"

void Shop::init() {
	auto& level = GameEngine::instance().getCurrentScene()->getLevelManager().getLevel();

	_active = true;
}

void Shop::render() {

	// render three squares in the center of the screen
	DrawRectangle(GetScreenWidth()/2 - 150, GetScreenHeight()/2 - 50, 100, 100, RED);
	DrawRectangle(GetScreenWidth()/2 - 50, GetScreenHeight()/2 - 50, 100, 100, GREEN); 
	DrawRectangle(GetScreenWidth()/2 + 50, GetScreenHeight()/2 - 50, 100, 100, BLUE);


}


void Shop::click(Vector2 position) {
	if (position.x > GetScreenWidth()/2 - 150 && position.x < GetScreenWidth()/2 - 50 && position.y > GetScreenHeight()/2 - 50 && position.y < GetScreenHeight()/2 + 50) {
		_active = false;
		GameEngine::instance().getCurrentScene()->resume();
	}

}