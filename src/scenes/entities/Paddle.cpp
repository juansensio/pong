#include "Paddle.h"

Paddle::Paddle(Entity* entity) : Object(entity) {}

Paddle::~Paddle() {}

void Paddle::init(const float& x, const float& y)
{
	float width = 10;
	float height = 100;

	_entity->add<CTransform>(Vector2{x, y}, Vector2{0, 0});
	_entity->add<CRectShape>(width, height, WHITE);
	_entity->add<CBoundingBox>(Vector2{width, height});

	_speed = 300;
}

void Paddle::collision(const Entity& entity)
{
	if (entity.tag() == EntityType::WALL) {
		_entity->get<CTransform>().velocity.y = 0;
	}
}
void Paddle::update(const float& dt) {}
