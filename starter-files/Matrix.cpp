#include <iostream>
#include <cassert>

#include "Matrix.hpp"

using namespace std;

// Initializes an empty Matrix
Matrix::Matrix() : m_width(0), m_height(0) {}

// Initializes a Matrix with the given dimensions and
// with each cell initialized to zero.
Matrix::Matrix(int width, int height) : Matrix(width, height, 0)
{
}

// Initializes a Matrix with the given dimensions and
// with each cell initialized to the value specified by fill_value.
Matrix::Matrix(int width, int height, int fill_value) : m_width(width), m_height(height)
{
    assert(fill_value <= 255 || fill_value >= 0);
    for (int i = 0; i < height * width; ++i)
    {
        m_data.push_back(fill_value);
    }
}


int Matrix::get_width() const
{
    return m_width;
}

int Matrix::get_height() const
{
    return m_height;
}

int &Matrix::at(int row, int column)
{
    assert(row >= 0);
    assert(column >= 0);
    assert(row < m_height);
    assert(column < m_width);

    return m_data.at(get_width() * row + column);
}

const int &Matrix::at(int row, int column) const
{
    assert(row >= 0);
    assert(column >= 0);
    assert(row < m_height);
    assert(column < m_width);

    return m_data.at(get_width() * row + column);
}

Matrix::Slice Matrix::get_row_slice(int row, int col_start, int col_end) const
{

    // Adjust col_start if it's less than 0
    if (col_start < 0)
    {
        col_start = 0;
    }

    // Adjust col_end if it's greater than the width of this matrix
    if (col_end > m_width)
    {
        col_end = m_width - 1;
    }

    // Ensure that col_start is strictly less than col_end
    assert(col_start < col_end);
    // row is out of bounds
    assert(row >= 0);
    // row is out of bounds
    assert(row <= m_height);

    std::vector<int> data;

    // Get row data
    for (int row = 0; row < m_height; row++)
    {
        for (int col = 0; col < m_width; col++)
        {
            data.push_back(m_data[row * m_width + col]);
        }
    }
    // Create and return a new Slice object
    return Slice{data, row, col_start, col_end};
}

void Matrix::print(std::ostream &os) const
{
    os << m_width << " " << m_height << endl;
    for (int row = 0; row < m_height; row++)
    {
        for (int col = 0; col < m_width; col++)
        {
            os << at(row, col) << " ";
        }
        os << endl;
    }
}
