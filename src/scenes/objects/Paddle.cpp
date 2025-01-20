#include "Paddle.h"

void Paddle::init(const float& x, const float& y)
{
	_height = 100;
	_width = 10;
	
	_entity->add<CTransform>(Vector2{x, y}, Vector2{0, 0});
	_entity->add<CRectShape>(_width, _height, WHITE);
	_entity->add<CInput>();
	_entity->add<CBoundingBox>(Vector2{_width, _height});

	_speed = 300;
}

void Paddle::collision(const std::shared_ptr<Entity>& entity)
{
	if (entity->tag() == EntityType::WALL) {
		_entity->get<CTransform>().velocity.y = 0;
	}
}

void Paddle::increaseSize(float size) {
	_height += size;
	_entity->get<CRectShape>().height = _height;
	_entity->get<CBoundingBox>().size = Vector2{_width, _height};
}