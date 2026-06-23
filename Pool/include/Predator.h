#pragma once

#include "Fish.h"
#include <vector>

class Victim;

class Predator : public Fish
{
public:
    explicit Predator(Position position);

    void move();

    void move(const std::vector<Victim> &victims, const Pool &pool);

    const Victim *findNearestVictim(
        const std::vector<Victim> &victims) const;
};