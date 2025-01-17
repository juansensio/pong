#pragma once

#include "Component.h"

class CBoundingBox : public Component
{
public:
    Rectangle rect;

    CBoundingBox() = default;
    CBoundingBox(const Rectangle& rect) : rect(rect) {}
}; 