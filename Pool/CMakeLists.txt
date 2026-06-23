cmake_minimum_required(VERSION 3.20)

project(PoolSimulation)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_library(
    PoolSimulation
    src/Distance.cpp
    src/Fish.cpp
    src/Victim.cpp
    src/Predator.cpp
    src/Simulation.cpp
    src/Pool.cpp    
)

target_include_directories(
    PoolSimulation
    PUBLIC include
)

add_executable(PoolApp
    src/main.cpp
)

target_link_libraries(PoolApp
    PRIVATE PoolSimulation
)

add_subdirectory(tests)