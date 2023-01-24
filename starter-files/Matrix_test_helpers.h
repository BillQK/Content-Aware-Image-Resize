#ifndef MATRIX_TEST_HELPERS_H
#define MATRIX_TEST_HELPERS_H

/* Matrix_test_helpers.h
 * Originally written by James Juett at the University of Michigan
 * for project 3 in EECS 280, Winter 2016.
 */

#include "Matrix.hpp"

// Returns true if mat1 and mat2 are the same size and
// contain exactly the same elements. Returns false otherwise.
bool Matrix_equal(const Matrix& mat1, const Matrix& mat2);

#endif // MATRIX_TEST_HELPERS_H
