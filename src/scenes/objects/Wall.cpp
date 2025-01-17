#include "Wall.h"

void Wall::init()
{
	_entity->add<CTransform>(Vector2{(float)GetScreenWidth()/2, (float)GetScreenHeight()/2}, Vector2{0, 0});
	_entity->add<CRectShape>(20, 200, WHITE);
	_entity->add<CInput>();

	_wall_speed = 300;
}

void Wall::update(const float& dt)
{
	const auto& input = _entity->get<CInput>();
	if (input.up) {
		_entity->get<CTransform>().velocity.y = - _wall_speed;
	} else if (input.down) {
		_entity->get<CTransform>().velocity.y = _wall_speed;
	} else {
		_entity->get<CTransform>().velocity.y = 0;
	}
}


void Wall::moveUp()
{
	_entity->get<CInput>().up = true;
}

void Wall::moveDown()
{
	_entity->get<CInput>().down = true;
}

void Wall::stop()
{
	_entity->get<CInput>().up = false;
	_entity->get<CInput>().down = false;
}