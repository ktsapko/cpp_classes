#include "Distance.h"

#include <cstdlib>

int manhattanDistance(
    const Position& a,
    const Position& b)
{
    return std::abs(a.row - b.row)
         + std::abs(a.col - b.col);
}