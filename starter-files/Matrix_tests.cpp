#include "Matrix.hpp"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"
#include <vector>

// Here's a free test for you! Model yours after this one.
// Add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix::at returns that value for each element.
TEST(test_Matrix_fill_basic)
{
  const int width = 3;
  const int height = 5;
  const int value = 42;
  auto mat = Matrix(width, height, value);

  for (int r = 0; r < height; ++r)
  {
    for (int c = 0; c < width; ++c)
    {
      ASSERT_EQUAL(mat.at(r, c), value);
    }
  }
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.h as needed.

// This is some macro magic that adds a main() function that runs the test cases
// defined in this file. Do not add your own main() function.
TEST(test_empty_matrix)
{
  Matrix m;
  ASSERT_EQUAL(m.get_width(), 0);
  ASSERT_EQUAL(m.get_height(), 0);
}

TEST(test_matrix_with_width_and_height_fill_value)
{
  Matrix m(3, 4, 5);
  ASSERT_EQUAL(m.get_width(), 3);
  ASSERT_EQUAL(m.get_height(), 4);

  for (int row = 0; row < m.get_height(); row++)
  {
    for (int col = 0; col < m.get_width(); col++)
    {
      ASSERT_EQUAL(m.at(row, col), 5);
    }
  }
}

TEST(test_matrix_with_width_height)
{
  Matrix m(3, 4);
  ASSERT_EQUAL(m.get_width(), 3);
  ASSERT_EQUAL(m.get_height(), 4);

  for (int row = 0; row < m.get_height(); row++)
  {
    for (int col = 0; col < m.get_width(); col++)
    {
      ASSERT_EQUAL(m.at(row, col), 0);
    }
  }
}

TEST(test_matrix_width_and_height_equals_zero)
{
  Matrix m(0, 0);
  ASSERT_EQUAL(m.get_width(), 0);
  ASSERT_EQUAL(m.get_height(), 0);
}
TEST(test_matrix_only_one_width_and_height_equals_zero)
{
  Matrix m1(0, 1);
  Matrix m2(1, 0);
  ASSERT_EQUAL(m1.get_width(), 0);
  ASSERT_EQUAL(m1.get_height(), 1);
  ASSERT_EQUAL(m2.get_width(), 1);
  ASSERT_EQUAL(m2.get_height(), 0);

}

TEST(test_matrix_width_and_height_equals_1)
{
  Matrix m1(1, 1);
  Matrix m2(1, 1);
  ASSERT_EQUAL(m1.get_height(), 1);
  ASSERT_EQUAL(m1.get_width(), 1);
  ASSERT_EQUAL(m2.get_height(), 1);
  ASSERT_EQUAL(m2.get_width(), 1);
}

TEST(test_Matrix_get_Width)
{
  const int width = 3;
  const int height = 5;
  const int value = 23;
  auto mat = Matrix(width, height, value);

  ASSERT_EQUAL(mat.get_width(), width);
}
TEST(test_Matrix_get_Height)
{
  const int width = 3;
  const int height = 5;
  const int value = 23;
  auto mat = Matrix(width, height, value);

  ASSERT_EQUAL(mat.get_height(), height);
}
TEST(test_Matrix_at)
{
  Matrix m(3, 4, 5);
  ASSERT_EQUAL(m.at(0, 0), 5);
  ASSERT_EQUAL(m.at(1, 2), 5);
  m.at(0, 0) = 6;
  ASSERT_EQUAL(m.at(0, 0), 6);
}

TEST(test_Matrix_get_row_slice)
{
  Matrix m(3, 4, 5);
  Matrix::Slice d = m.get_row_slice(0, 1, 2);
  ASSERT_EQUAL(d.row, 0);
  ASSERT_EQUAL(d.col_start, 1);
  ASSERT_EQUAL(d.col_end, 2);
  ASSERT_EQUAL(d.data.at(0), 5);
  ASSERT_EQUAL(d.data.at(1), 5);
}

TEST(test_Matrix_get_row_slice_with_negative_negative)
{
  Matrix m(3, 4, 5);
  Matrix::Slice d = m.get_row_slice(1, -1, 2);
  // Assert that the row index is not negative
  ASSERT_TRUE(d.col_start == 0);
}

TEST(test_Matrix_get_row_slice_with_col_end_greater_than_width)
{
  Matrix m(3, 4, 5);
  Matrix::Slice d = m.get_row_slice(1, 1, 4);
  // Assert that the row index is not negative
  ASSERT_TRUE(d.col_end == 2);
}

TEST(test_Matrix_get_row_slice_with_out_of_bounds_end_column)
{
  Matrix m(3, 4, 5);
  Matrix::Slice d = m.get_row_slice(0, 1, 100);
  // Assert that the end column is within the bounds of the matrix
  ASSERT_TRUE(d.col_end >= 0 && d.col_end < m.get_width());
}

TEST_MAIN()
