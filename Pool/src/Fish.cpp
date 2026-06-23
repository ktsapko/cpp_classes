#include "Fish.h"

Fish::Fish(Position position)
    : m_position(position)
{
}

Position Fish::getPosition() const
{
    return m_position;
}