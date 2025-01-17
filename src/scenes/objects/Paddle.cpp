#include "Paddle.h"

void Paddle::init(const float& x, const float& y)
{
	float width = 10;
	float height = 100;

	_entity->add<CTransform>(Vector2{x, y}, Vector2{0, 0});
	_entity->add<CRectShape>(width, height, WHITE);
	_entity->add<CInput>();
	_entity->add<CBoundingBox>(Rectangle{x - width/2, y - height/2, width, height});

	_speed = 300;
}

void Paddle::update(const float& dt)
{
}
