#include "Predator.h"
#include "Victim.h"
#include <vector>
#include <climits>
#include "Distance.h"
#include "Fish.h"
#include "Pool.h"

void Predator::move()
{
    // Default move for abstract interface compatibility.
}

void Predator::move(
    const std::vector<Victim>& victims,
    const Pool& pool)
{
    auto nearest = findNearestVictim(victims);

    if (!nearest)
    {
        return;
    }

    auto target = nearest->getPosition();

    Position newPosition = m_position;

    for (int i = 0; i < 2; ++i)
    {
        if (newPosition.row < target.row)
        {
            ++newPosition.row;
        }
        else if (newPosition.row > target.row)
        {
            --newPosition.row;
        }
        else if (newPosition.col < target.col)
        {
            ++newPosition.col;
        }
        else if (newPosition.col > target.col)
        {
            --newPosition.col;
        }

        if (pool.isInside(newPosition))
        {
            m_position = newPosition;
        }
    }
}

Predator::Predator(Position position)
    : Fish(position)
{
   
}

const Victim *Predator::findNearestVictim(
    const std::vector<Victim> &victims) const
{
    const Victim *nearest = nullptr;
    int minDistance = INT_MAX;

    for (const auto &victim : victims)
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