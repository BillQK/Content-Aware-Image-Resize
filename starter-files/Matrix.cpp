#include <iostream>
#include <cassert>

#include "Matrix.hpp"

using namespace std;

// Initializes an empty Matrix
Matrix::Matrix(): m_width(0), m_height(0) {}

// Initializes a Matrix with the given dimensions and
// with each cell initialized to zero.
Matrix::Matrix(int width, int height): Matrix{width, height, 0} {}

// Initializes a Matrix with the given dimensions and
// with each cell initialized to the value specified by fill_value.
Matrix::Matrix(int width, int height, int fill_value): m_width(width), m_height(height) {
    assert (fill_value <= 255 && fill_value >= 0);
    for(int i = 0; i < height * width; ++i){
        m_data.push_back(fill_value);
    }
}

int Matrix::get_width() const {
    return m_width;
}

int Matrix::get_height() const {
    return m_height;
}

int& Matrix::at(int row, int column) {
    assert (row >= 0);
    assert (column >= 0);
    assert (row <= m_height);
    assert (column <= m_width);

    return m_data.at(m_width*row+column);
}

const int& Matrix::at(int row, int column) const {
    // assert ((row >= 0) && (column >= 0) && (row < m_height) && (column < m_width));
    return m_data.at(m_width*row+column);
}

Matrix::Slice Matrix::get_row_slice(int row, int col_start, int col_end) const {
    assert(col_start<col_end);
    assert(row>=0);
    assert(row<=m_height);

    vector<int> data;
    Slice s = Slice{data, row, col_start, col_end};

    if(col_start < 0) {
        // ret slice, first element is 0
        col_start = 0;
    }
    if(col_end > m_width) {
        // ret slice is last element
        col_end = m_width;
    }

    // row is height, col start/end is width, so get a slice @ a row
    for(int i = col_start; i<col_end; i++) {
        data.push_back(at(row, i));
    }
    return s;
}

void Matrix::print(std::ostream& os) const {
    os << m_width << " " << m_height << endl;
    int index = 0;
    for(int row = 0; row<m_height; row++) {
        for(int col = 0; col<m_width; col++) {
            // q: is this how to add a space after a variable?
            // better to use .at(index) bc it'll give an error when go oob for [index]
            os << m_data.at(index) << " ";
            index++;
        }
        os << "\n";
    }
}
