#pragma once

#include "Component.h"

class CTransform : public Component
{
public:
    Vector2 position = { 0., 0. };
    Vector2 prevPosition = { 0., 0. };
    Vector2 velocity = { 0., 0. };

    CTransform() {}
    CTransform(const Vector2& position, const Vector2& velocity) 
        : position(position)
        , velocity(velocity) {}
}; 