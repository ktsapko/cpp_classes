#include <gtest/gtest.h>
#include "Predator.h"
#include "Victim.h"
#include "Position.h"
#include <vector>
#include "Simulation.h"
#include "Pool.h"

TEST(Predator, MovesTowardsNearestVictim)
{
    Predator predator({0, 0});

    std::vector<Victim> victims{
        Victim({5, 0})};

    Pool pool(20, 20);
    predator.move(victims, pool);

    const Position expectedPosition{2, 0};
    EXPECT_EQ(expectedPosition, predator.getPosition())
        << "Predator should move towards the nearest victim.";
}

TEST(Predator, EatsVictimOnSameCell)
{
    Predator predator({0, 0});

    std::vector<Victim> victims{
        Victim({2, 0})};

    Pool pool(20, 20);
    predator.move(victims, pool);

    const Position expectedPosition{2, 0};
    EXPECT_EQ(
        expectedPosition,
        predator.getPosition());
}

TEST(Simulation, RunsSeveralIterations)
{
    std::vector<Victim> victims{
        Victim({5, 5}),
        Victim({7, 7})};

    std::vector<Predator> predators{
        Predator({0, 0})};

    Pool pool(20, 20);
    Simulation simulation(
        std::move(victims),
        std::move(predators),
        pool);

    EXPECT_NO_THROW(
        simulation.run(10));
}

TEST(Pool, PositionInsidePool)
{
    Pool pool(10, 10);

    EXPECT_TRUE(
        pool.isInside({0, 0}));

    EXPECT_TRUE(
        pool.isInside({9, 9}));

    EXPECT_FALSE(
        pool.isInside({-1, 0}));

    EXPECT_FALSE(
        pool.isInside({10, 0}));

    EXPECT_FALSE(
        pool.isInside({0, 10}));
}

TEST(Victim, CannotLeavePool)
{
    Pool pool(10, 10);

    Victim victim({0, 0});

    for (int i = 0; i < 1000; ++i)
    {
        victim.move(pool);

        auto pos = victim.getPosition();

        EXPECT_TRUE(pool.isInside(pos));
    }
}