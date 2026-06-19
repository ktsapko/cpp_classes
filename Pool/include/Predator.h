#pragma once
#include "Fish.h"


class Predator : public Fish
{
public:
    void move() override;
    
    const Victim* findNearestVictim(
        const std::vector<Victim>& victims) const;
};