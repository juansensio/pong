#pragma once

#include "Component.h"

class CBoundingBox : public Component
{
public:
    Vector2 min;
    Vector2 max;

    CBoundingBox() = default;
    CBoundingBox(const Vector2& min, const Vector2& max) : min(min), max(max) {}
}; 