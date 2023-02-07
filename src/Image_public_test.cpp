#include <sstream>
#include <string>

#include "Image.hpp"
#include "Image_test_helpers.h"
#include "unit_test_framework.h"

using std::string;
using std::stringstream;


// This is the public Image test for which the autograder gives feedback.
// It only tests VERY FEW of the expected behaviors of the Image module.
// You must write your own comprehensive unit tests in Image_tests.cpp.

TEST(test_image_basic) {
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
  stringstream ss;
  img.print(ss);

  // Correct output
  string correct = "P3\n2 2\n255\n255 0 0 0 255 0 \n0 0 255 255 255 255 \n";
  ASSERT_EQUAL(correct, ss.str());
}

TEST(test_image_from_and_to_stream) {
  // A very poorly behaved (but still valid) input PPM.
  string input = "P3 2 2\t255 255 0 0\n0\n255 0 \n0 0 255 255 255 255 \n";
  std::istringstream ss_input(input);
  Image img = Image::read_ppm(ss_input);

  // Should be well behaved when you print it though!
  string output_correct = "P3\n2 2\n255\n255 0 0 0 255 0 \n0 0 255 255 255 255 \n";
  std::ostringstream ss_output;
  img.print(ss_output);
  string actual = ss_output.str();
  std::cout << actual << std::endl;
  ASSERT_EQUAL(actual, output_correct);
}

TEST_MAIN()
