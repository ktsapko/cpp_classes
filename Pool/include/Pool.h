#pragma once

class Pool
{
public:
    Pool(int rows, int cols);
    int rows() const;
    int cols() const;

private:
    int m_rows;
    int m_cols;
};