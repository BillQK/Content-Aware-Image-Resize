
/* Matrix_test_helpers.cpp
 * Originally written by James Juett at the University of Michigan
 * for project 3 in EECS 280, Winter 2016.
 */

#include "Matrix_test_helpers.h"

bool Matrix_equal(const Matrix& mat1, const Matrix& mat2){
  if (mat1.get_width() != mat2.get_width()){ return false; }
  if (mat1.get_height() != mat2.get_height()){ return false; }

  for(int r = 0; r < mat1.get_height(); ++r){
    for(int c = 0; c < mat1.get_width(); ++c){
      if (mat1.at(r, c) != mat2.at(r, c)){ return false; }
    }
  }

  return true;
}
