#include "Death.h"

Death::Death(Entity* entity) : Object(entity) {}

Death::~Death() {}

void Death::init()
{
	_entity->add<CTransform>(Vector2{0, 0}, Vector2{0, 0});
	_entity->add<CBoundingBox>(Vector2{100, 100});
}


