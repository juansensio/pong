#include "Death.h"

void Death::init()
{
	_entity->add<CBoundingBox>(Rectangle{0, 0, 100, 100});
}


