TEST(Predator, FindsNearestVictim)
{
    Predator predator({0,0});

    std::vector<Victim> victims
    {
        Victim({5,5}),
        Victim({1,1}),
        Victim({10,10})
    };

    auto nearest =
        predator.findNearestVictim(victims);

    EXPECT_EQ(
        Position{1,1},
        nearest->getPosition());
}