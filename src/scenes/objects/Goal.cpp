#include "Goal.h"

Goal::Goal(Entity* entity) : Object(entity) {}

Goal::~Goal() {}

void Goal::init()
{
	float screenHeight = GetScreenHeight();
	float screenWidth = GetScreenWidth();
	// _entity->add<CTransform>(Vector2{screenWidth - 5, screenHeight / 2}, Vector2{0, 0});
	_entity->add<CTransform>(Vector2{screenWidth + 15, screenHeight / 2}, Vector2{0, 0});
	_entity->add<CBoundingBox>(Vector2{10, screenHeight});
}


