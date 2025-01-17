#include "Goal.h"

void Goal::init()
{
	_entity->add<CBoundingBox>(Rectangle{0, 0, 100, 100});
}


