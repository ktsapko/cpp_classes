#pragma once

#include "Victim.h"
#include "Predator.h"
#include <cstddef>
#include "Pool.h"

#include <vector>

class Simulation
{
public:
    Simulation(
        std::vector<Victim> victims,
        std::vector<Predator> predators, 
        Pool pool);
    size_t victimCount() const
    {
        return m_victims.size();
    }

    void run(size_t iterations);

private:
    std::vector<Victim> m_victims;
    std::vector<Predator> m_predators;
    void removeEatenVictims();
    Pool m_pool;
};