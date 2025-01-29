#include "Wall.h"

Wall::Wall(Entity* entity) : Object(entity) {}

Wall::~Wall() {}

void Wall::init()
{
	_entity->add<CTransform>(Vector2{(float)GetScreenWidth()/2, (float)GetScreenHeight()/2}, Vector2{0, 0});
	_entity->add<CRectShape>(20, 200, WHITE);
}
