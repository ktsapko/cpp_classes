#pragma once

#include "Position.h"

class Fish
{
public:
    virtual ~Fish() = default;
    virtual Position getPosition() const;
    virtual void move() = 0;

protected:
    Position m_position;
};