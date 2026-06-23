#include "Simulation.h"
#include "Pool.h"
#include "Victim.h"
#include "Predator.h"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

int main()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    constexpr int rows = 20;
    constexpr int cols = 20;

    constexpr int victimCount = 10;
    constexpr int predatorCount = 2;

    constexpr int iterations = 100;

    Pool pool(rows, cols);

    std::vector<Victim> victims;
    std::vector<Predator> predators;

    for (int i = 0; i < victimCount; ++i)
    {
        victims.emplace_back(
            Position{
                rand() % rows,
                rand() % cols
            });
    }

    for (int i = 0; i < predatorCount; ++i)
    {
        predators.emplace_back(
            Position{
                rand() % rows,
                rand() % cols
            });
    }

    Simulation simulation(
        std::move(victims),
        std::move(predators),
        pool);

    simulation.run(iterations);

    std::cout
        << "Victims left: "
        << simulation.victimCount()
        << '\n';

    return 0;
}