#include "Matrix.hpp"

#include <cassert>
#include <iostream>

using namespace std;

// Initializes an empty Matrix
Matrix::Matrix() : m_width(0), m_height(0) {}

// Initializes a Matrix with the given dimensions and
// with each cell initialized to zero.
Matrix::Matrix(int width, int height) : Matrix{width, height, 0} {}

// Initializes a Matrix with the given dimensions and
// with each cell initialized to the value specified by fill_value.
Matrix::Matrix(int width, int height, int fill_value) : m_width(width), m_height(height) {
  assert(fill_value <= 255 && fill_value >= 0);
  for (int i = 0; i < height * width; ++i) {
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
  assert(row >= 0);
  // assert(column >= 0);
  assert(row < m_height);
  assert(column < m_width);

  return m_data.at(get_width() * row + column);
}

const int& Matrix::at(int row, int column) const {
  assert(row >= 0);
  // assert(column >= 0);
  assert(row < m_height);
  assert(column < m_width);

  return m_data.at(get_width() * row + column);
}

Matrix::Slice Matrix::get_row_slice(int row, int col_start, int col_end) const {
  assert(col_start < col_end);
  assert(row >= 0);
  assert(row < m_height);

  vector<int> data = vector<int>();
  // if start < 0, col_start is 0, if end > width, col_end the last column
  col_start = max(0, col_start);
  col_end = min(m_width, col_end);

  // push the cell values into the slice data vector
  for (int i = col_start ; i < col_end; i++) {
    data.push_back(at(row , i));
  }

  Slice s = Slice{data, row, col_start, col_end};

  return s;
}

void Matrix::print(std::ostream& os) const {
  os << m_width << " " << m_height << endl;
  int index = 0;
  for (int row = 0; row < m_height; row++) {
    for (int col = 0; col < m_width; col++) {
      os << m_data.at(index) << " ";
      index++;
    }
    os << endl;
  }
}
