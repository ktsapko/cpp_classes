add_executable(
    Predator_Test
    Predator_Test.cpp
)

target_link_libraries(
    Predator_Test
    PRIVATE PoolSimulation
    PRIVATE gtest
    PRIVATE gmock
    PRIVATE gmock_main
)

include(GoogleTest)

gtest_discover_tests(
    Predator_Test
)