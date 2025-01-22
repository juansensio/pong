#pragma once

#include "entities/Entity.h"

struct Overlaps {
	Vector2 overlap;
	Vector2 prevOverlap;
};

class Physics {
public:
	Physics();
	~Physics();

	static Overlaps BoundingBoxOverlap(Entity& entity1, Entity& entity2);
};