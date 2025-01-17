#include "Paddle.h"

void Paddle::init()
{
	float screen_width = (float)GetScreenWidth();
	float screen_height = (float)GetScreenHeight();

	float x = 10;
	float y = screen_height / 2;
	float width = 10;
	float height = 100;

	_entity->add<CTransform>(Vector2{x, y}, Vector2{0, 0});
	_entity->add<CRectShape>(width, height, WHITE);
	_entity->add<CInput>();
	_entity->add<CBoundingBox>(
		Vector2{x - width/2, y - height/2}, 
		Vector2{x + width/2, y + height/2}
	);

	_paddle_speed = 300;
}

void Paddle::update(const float& dt)
{
}
