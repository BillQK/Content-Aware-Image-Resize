// Project UID af1f95f547e44c8ea88730dfb185559d

#include <sstream>

#include "Matrix.hpp"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"

using std::ostringstream;

// This is the public Matrix test for which the autograder gives feedback.
// It only tests VERY FEW of the expected behaviors of the Matrix module.
// You must write your own comprehensive unit tests in Matrix_tests.cpp.

TEST(test_Matrix_fill_basic)
{
  const int width = 3;
  const int height = 5;
  const int value = 42;
  auto mat = Matrix(width, height, value);

  for(int r = 0; r < height; ++r) {
    for(int c = 0; c < width; ++c) {
      ASSERT_EQUAL(mat.at(r, c), value);
    }
  }
}

TEST(test_Matrix_print) {
  auto mat = Matrix(1, 1, 42);

  ostringstream expected;
  expected << "1 1\n"
           << "42 \n";
  ostringstream actual;
  mat.print(actual);
  ASSERT_EQUAL(expected.str(), actual.str());
}

TEST_MAIN()
