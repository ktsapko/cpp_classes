#include "Simulation.h"

#include <algorithm>
#include <iostream>

Simulation::Simulation(
    std::vector<Victim> victims,
    std::vector<Predator> predators,
    Pool pool)
    : m_victims(std::move(victims)),
      m_predators(std::move(predators)),
      m_pool(pool)
{
}

void Simulation::run(size_t iterations)
{ 
    for (size_t i = 0; i < iterations; ++i)
    {
        std::cout
            << "Iteration "
            << i + 1
            << " Victims: "
            << victimCount()
            << '\n';

        for (auto &victim : m_victims)
        {
            victim.move(m_pool);
        }

        for (auto &predator : m_predators)
        {
            predator.move(m_victims, m_pool);
        }
        removeEatenVictims();
    }
}

void Simulation::removeEatenVictims()
{
    m_victims.erase(
        std::remove_if(
            m_victims.begin(),
            m_victims.end(),
            [this](const Victim &victim)
            {
                for (const auto &predator : m_predators)
                {
                    if (predator.getPosition() ==
                        victim.getPosition())
                    {
                        return true;
                    }
                }
                return false;
            }),
        m_victims.end());
}