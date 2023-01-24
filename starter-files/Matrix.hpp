#ifndef MATRIX_H
#define MATRIX_H

/* Matrix.hpp
 *
 * DO NOT MODIFY THIS FILE
 *
 * Adapted by James Perretta at Northeastern University, Spring 2023.
 * Originally written by James Juett at the University of Michigan
 * for project 3 in EECS 280, Winter 2016.
 *
 * The Matrix module is based on an earlier project by
 * Andrew DeOrio.
 */

// Contains declarations (not definitions!) for the iostream library. You will need
// to include iostream in Matrix.cpp.
#include <iosfwd>
#include <vector>

// Representation of a 2D matrix of integers
// The "final" keyword prevents inheriting from this class.
class Matrix final {
public:
  // Initializes an empty Matrix
  Matrix();

  // Initializes a Matrix with the given dimensions and
  // with each cell initialized to zero.
  Matrix(int width, int height);

  // Initializes a Matrix with the given dimensions and
  // with each cell initialized to the value specified by fill_value.
  Matrix(int width, int height, int fill_value);

  // Returns the width of this Matrix.
  int get_width() const;

  // Returns the height of this Matrix.
  int get_height() const;

  // Returns a modifiable reference to the cell at the given row and column.
  // If row or column are out of bounds (either less than zero or row >= height
  // or column >= width, the behavior is undefined.
  int& at(int row, int column);

  // Returns a non-modifiable reference to the cell at the given row and column.
  // If row or column are out of bounds (either less than zero or row >= height
  // or column >= width, the behavior is undefined.
  const int& at(int row, int column) const;

  struct Slice {
    std::vector<int> data;
    int row;
    int col_start;
    int col_end;
  };

  // Returns a Slice representing the data from the requested portion of the
  // specified row. The range [col_start, col_end) is inclusive of col_start
  // and exclusive of col_end.
  // - If col_start is less than zero, the first element of the returned slice
  // will be the first element of the row.
  // of the row.
  // - If col_end is greater than the width of this Matrix, the last element of
  // the returned slice will be the last element of the row.
  // - col_start must be strictly less than col_end, otherwise the behavior is undefined.
  // - If row is out of bounds (less than zero or >= height), the behavior is undefined.
  //
  // The members col_start and col_end of the returned Slice will reflect
  // any adjustments made to the input parameters.
  // For example, if this method is called with the col_start argument set to -1,
  // the value of col_start in the returned Slice object will instead be zero.
  //
  // Note: When defining this method in Matrix.cpp, you will need to change
  // The return type from Slice to Matrix::Slice. In the body of the method
  // definition, you will be able to refer to it as Slice.
  Slice get_row_slice(int row, int col_start, int col_end);

  // Prints this Matrix to the stream referenced by os as follows:
  // First, prints the width and height for the Matrix to os:
  // WIDTH [space] HEIGHT [newline]
  // Then prints the rows of the Matrix to os with one row per line.
  // Each element is followed by a space and each row is followed
  // by a newline. This means there will be an "extra" space at
  // the end of each line.
  void print(std::ostream& os) const;

private:
  // The leading m_ is one possible naming convention for private member variables.
  int m_width;
  int m_height;
  // Used to store data for a 2D matrix.
  // Refer to lecture 3 for some hints.
  std::vector<int> m_data;
};

#endif // MATRIX_H
