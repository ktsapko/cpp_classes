#include "Victim.h"
#include "Directions.h"
#include "Pool.h"

Victim::Victim(Position position)
    : Fish(position)
{
}

void Victim::move(const Pool& pool)
{
   randomMove(pool);
}

void Victim::randomMove(const Pool& pool)
{
   Position newPosition = m_position;

   Direction direction =
       static_cast<Direction>(rand() % 4);

   switch (direction)
   {
   case Direction::Up:
      --newPosition.row;
      break;

   case Direction::Down:
      ++newPosition.row;
      break;

   case Direction::Left:
      --newPosition.col;
      break;

   case Direction::Right:
      ++newPosition.col;
      break;
   }
   if (pool.isInside(newPosition))
   {
      m_position = newPosition;
   }
}