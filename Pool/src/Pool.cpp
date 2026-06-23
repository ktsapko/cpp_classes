#include "Pool.h"

Pool::Pool(int rows, int cols)
    : m_rows(rows),
      m_cols(cols)
{
}

bool Pool::isInside(
    const Position& position) const
{
    return position.row >= 0 &&
           position.row < m_rows &&
           position.col >= 0 &&
           position.col < m_cols;
}