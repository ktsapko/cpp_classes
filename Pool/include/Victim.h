#pragma once

#include "Fish.h"

class Pool;

class Victim : public Fish
{
public:
    explicit Victim(Position position);

    void move(const Pool& pool);

private:
    void randomMove(const Pool& pool);
};