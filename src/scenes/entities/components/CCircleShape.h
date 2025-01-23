#pragma once

#include "Component.h"

class CCircleShape : public Component
{
public:
    Color color; 
    float radius;

    CCircleShape() {}
    CCircleShape(float radius, const Color& color) 
        : color(color)
        , radius(radius) {}
}; 