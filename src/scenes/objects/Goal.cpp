#include "Goal.h"

void Goal::init()
{
	float screenHeight = GetScreenHeight();
	_entity->add<CBoundingBox>(Rectangle{0, 0, 10, screenHeight});
}


