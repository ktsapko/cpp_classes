#pragma once

#include "Fish.h"
#include "Position.h"

class Victim : public Fish
{
public:
    explicit Victim(Position position);
    void move();
    Position getPosition() const;

private:
    Position m_position;
};