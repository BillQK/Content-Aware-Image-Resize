#include <iostream>
#include <cassert>

#include "Matrix.hpp"

using namespace std;

// Initializes an empty Matrix
Matrix::Matrix() : m_width(0), m_height(0) {}

// Initializes a Matrix with the given dimensions and
// with each cell initialized to zero.
Matrix::Matrix(int width, int height) : Matrix(width, height, 0) {}

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

const int& Matrix::at(int row, int column) const {
    assert(row>=0);
    assert(column>=0);
    assert(row<m_height);
    assert(column<m_width);
    return m_data.at(get_width()*row+column);
}

Matrix::Slice Matrix::get_row_slice(int row, int col_start, int col_end) const {
    assert(col_start<col_end);
    assert(row>=0);
    assert(row<m_height);

    vector<int> data;
    Slice s = Slice{data, row, col_start, col_end};

    // Get the slice of data at the specified row and columns
    for (int i = col_start; i <= col_end; i++)
    {
        s.data.push_back(at(row, i));
    }
    return s;
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
