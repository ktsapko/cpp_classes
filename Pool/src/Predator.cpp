#include "Predator.h"
#include "Victim.h"
#include <vector>
#include "Distance.h"
#include "Fish.h"

void Predator::move()
{
    // Implement predator movement logic here
}

const Victim* Predator::findNearestVictim(
    const std::vector<Victim>& victims) const
{
    const Victim* nearest = nullptr;
    int minDistance = INT_MAX;

    for (const auto& victim : victims)
    {
        auto currentDistance =
            manhattanDistance(
                m_position,
                victim.getPosition());

        if (currentDistance < minDistance)
        {
            minDistance = currentDistance;
            nearest = &victim;
        }
    }

    return nearest;
}