#pragma once

#include "Component.h"

class CInput : public Component
{
public:
    bool up = false;
    bool down = false;

    CInput() = default;
}; 