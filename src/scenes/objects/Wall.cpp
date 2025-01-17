#include "Wall.h"

void Wall::init(const float& y)
{
	float screenWidth = GetScreenWidth();
	float width = 20;

	_entity->add<CTransform>(Vector2{(float)screenWidth/2, y}, Vector2{0, 0});
	_entity->add<CRectShape>(screenWidth, width, WHITE);
	_entity->add<CBoundingBox>(Vector2{0, y - width / 2}, Vector2{screenWidth, y + width / 2});
}


