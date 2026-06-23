#pragma once

#include "Position.h"

class Pool;

class Fish
{
public:
    explicit Fish(Position position);

    virtual ~Fish() = default;

    Position getPosition() const;

protected:
    Position m_position;
};