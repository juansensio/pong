#pragma once

#include "entities/Entity.h"

struct Overlaps {
	Vector2 overlap;
	Vector2 prevOverlap;
};

class Physics {
public:
	Physics() = default;
	~Physics() = default;

	static Overlaps BoundingBoxOverlap(const std::shared_ptr<Entity>& entity1, const std::shared_ptr<Entity>& entity2);
};