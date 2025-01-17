#include "Death.h"

void Death::init()
{
	float screenHeight = GetScreenHeight();
	float screenWidth = GetScreenWidth();
	_entity->add<CBoundingBox>(Rectangle{screenWidth - 10, 0, 10, screenHeight});
}


