#pragma once

#include "Component.h"

class CAI : public Component
{
public:
    float speed;
    
    CAI() {}
    CAI(float speed) : speed(speed) {}
};