#pragma once

#include "Position.h"

class Pool
{
public:
    Pool(int rows, int cols);

    bool isInside(
        const Position& position) const;

private:
    int m_rows;
    int m_cols;
};