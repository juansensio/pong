#include "Goal.h"

void Goal::init()
{
	_entity->add<CTransform>(Vector2{0, 0}, Vector2{0, 0});
	_entity->add<CBoundingBox>(Vector2{100, 100});
}


