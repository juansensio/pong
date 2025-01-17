#include "Goal.h"

void Goal::init()
{
	_entity->add<CBoundingBox>(Vector2{0, 0}, Vector2{100, 100});
}


