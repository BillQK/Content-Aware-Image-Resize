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

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(mat.at(r, c), value);
    }
  }
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.h as needed.

// This is some macro magic that adds a main() function that runs the test cases
// defined in this file. Do not add your own main() function.

TEST(test_Matrix_fill) {
// 2 constructors
}
TEST(test_Matrix_get_Width) {
  const int width = 3; 
  const int height = 5; 
  const int value = 23; 
  auto mat = Matrix(width, height, value); 

  ASSERT_EQUAL(mat.get_width(), width);

}
TEST(test_Matrix_get_Height) {
  const int width = 3; 
  const int height = 5; 
  const int value = 23; 
  auto mat = Matrix(width, height, value); 

  ASSERT_EQUAL(mat.get_height(), height);

}
TEST(test_Matrix_at) {
  const int width = 3; 
  const int height = 5; 
  const int value = 23; 
  auto mat = Matrix(width, height, value); 
  mat.at(2,3) = 25;

  ASSERT_EQUAL(mat.at(2,3), 25);
}

TEST(test_Matrix_get_row_slice) {
  const int width = 3; 
  const int height = 5; 
  const int value = 23; 
  auto mat = Matrix(width, height, value); 
  const int row = 2;
  const int col_start = 3; 
  const int col_end = 5;
  // mat.at(row, 3) = 25; 

  std::vector<int> data = {23,23,23};
  
  auto s = Matrix::Slice{data, row, col_start, col_end};
  auto s1 = mat.get_row_slice(row, col_start, col_end);
  ASSERT_EQUAL(s1.data.at(0), 23);
  // ASSERT_EQUAL(s1.row, 2);
}

TEST_MAIN()
