#include "Matrix.hpp"
#include "Image_test_helpers.h"
#include "unit_test_framework.h"
#include <iostream>
#include <string>
#include <sstream>
#include <istream>
#include <fstream>

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

TEST(test_readppm) {

  string filename = "dog_4x5.correct.ppm";
  ifstream file(filename);

  Image img; 
  img = img.read_ppm(file); 
  cout << img.get_height() << " " << img.get_width() << endl;
  ostringstream actual; 
  img.print(actual);

  ostringstream correct;
  correct << "P3\n4 5\n255\n";
  correct << "0 0 0 255 255 250 0 0 0 0 0 0 \n";
  correct << "255 255 250 126 66 0 126 66 0 255 255 250 \n";
  correct << "126 66 0 0 0 0 0 0 0 126 66 0 \n";
  correct << "255 219 183 255 219 183 255 219 183 255 219 183 \n";
  correct << "255 219 183 134 0 0 0 0 0 255 219 183 \n";

  ASSERT_EQUAL(correct.str(), actual.str());

  // if(is.is_open()) {
  //   Image::readppm(is);
  // }
}

TEST(test_get_width) {

}

TEST(test_get_height) {

}

TEST(test_get_pixel) {

}

TEST(test_set_pixel) {

}

// This is some macro magic that adds a main() function that runs the test cases
// defined in this file. Do not add your own main() function.
TEST_MAIN()
