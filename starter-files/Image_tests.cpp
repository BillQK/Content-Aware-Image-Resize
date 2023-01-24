#include "Matrix.hpp"
#include "Image_test_helpers.h"
#include "unit_test_framework.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// Here's a free test for you! Model yours after this one.
// Add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image::print produces the correct output.
TEST(test_print_basic) {
  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image img(2, 2);
  img.set_pixel(0, 0, red);
  img.set_pixel(0, 1, green);
  img.set_pixel(1, 0, blue);
  img.set_pixel(1, 1, white);

  // Capture our output
  ostringstream actual;
  img.print(actual);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(correct.str(), actual.str());
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Image_test_helpers.h as needed.

// This is some macro magic that adds a main() function that runs the test cases
// defined in this file. Do not add your own main() function.
TEST_MAIN()
