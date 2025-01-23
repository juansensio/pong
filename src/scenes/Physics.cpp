#include "Physics.h"

Physics::Physics() {}

Physics::~Physics() {}

Overlaps Physics::BoundingBoxOverlap(Entity& entity1, Entity& entity2) {
	const auto& bb1 = entity1.get<CBoundingBox>();
	const auto& bb2 = entity2.get<CBoundingBox>();
	const auto& position1 = entity1.get<CTransform>().position;
	const auto& position2 = entity2.get<CTransform>().position;
	// detect collision
	Vector2 delta = {
		abs(position1.x - position2.x),
		abs(position1.y - position2.y)
	};
	Vector2 overlap = {
		bb1.halfSize.x + bb2.halfSize.x - abs(delta.x),
		bb1.halfSize.y + bb2.halfSize.y - abs(delta.y)
	};
	if (overlap.x > 0 && overlap.y > 0) {
		// resolve collision
		const auto& prevPos1 = entity1.get<CTransform>().prevPosition;
		const auto& prevPos2 = entity2.get<CTransform>().prevPosition;
		Vector2 prevDelta = {
			abs(prevPos1.x - prevPos2.x),
			abs(prevPos1.y - prevPos2.y)
		};
		Vector2 prevOverlap = {
			bb1.halfSize.x + bb2.halfSize.x - abs(prevDelta.x),
			bb1.halfSize.y + bb2.halfSize.y - abs(prevDelta.y)
		};
		if (prevOverlap.y > 0 && prevOverlap.x <= 0) { // side collision
			if (prevPos1.x < prevPos2.x) {
				entity1.get<CTransform>().position.x -= overlap.x;
			} else {
				entity1.get<CTransform>().position.x += overlap.x;
			}
		} else if (prevOverlap.x > 0 && prevOverlap.y <= 0) { // top/bottom collision
			if (prevPos1.y < prevPos2.y) { // bottom collision
				entity1.get<CTransform>().position.y -= overlap.y;
			} else { // top collision
				entity1.get<CTransform>().position.y += overlap.y;
			}
		} else { // diagonal collision
			// move ball to the side since will always be a paddle
			if (prevPos1.x < prevPos2.x) { 
				entity1.get<CTransform>().position.x -= overlap.x;
			} else {
				entity1.get<CTransform>().position.x += overlap.x;
			}
		}
		return {
			overlap,
			prevOverlap
		};
	}
	return {
		overlap,
		Vector2{0, 0}
	};
}