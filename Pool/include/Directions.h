#include "Position.h"
#include <cstdlib>

enum class Direction
{
    Up,
    Down,
    Left,
    Right
};

void randomMove(Position &position)
{
    Direction direction = static_cast<Direction>(rand() % 4);
    switch (direction)
    {
    case Direction::Up:
        position.row--;
        break;
    case Direction::Down:
        position.row++;
        break;
    case Direction::Left:
        position.col--;
        break;
    case Direction::Right:
        position.col++;
        break;
    }
}
