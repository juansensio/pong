#include "Death.h"

Death::Death(Entity* entity) : Object(entity) {}

Death::~Death() {}

void Death::init()
{
	float screenHeight = GetScreenHeight();
	float screenWidth = GetScreenWidth();
		// _entity->add<CTransform>(Vector2{5, screenHeight / 2}, Vector2{0, 0});
	_entity->add<CTransform>(Vector2{-15, screenHeight / 2}, Vector2{0, 0});
	_entity->add<CBoundingBox>(Vector2{10, screenHeight});
}


