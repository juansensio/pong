#pragma once

#include "Component.h"

class CBoundingBox : public Component
{
public:
    Vector2 size;
    Vector2 halfSize;

    CBoundingBox() = default;
    CBoundingBox(const Vector2& size) : size(size), halfSize(Vector2{size.x / 2, size.y / 2}) {}
}; 