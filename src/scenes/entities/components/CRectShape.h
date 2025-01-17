#pragma once

#include "Component.h"

class CRectShape : public Component
{
public:
    Color color; 
    float width;
    float height;
	
    CRectShape() = default;
    CRectShape(float width, float height, const Color& color) 
        : color(color), width(width), height(height) {}
}; 