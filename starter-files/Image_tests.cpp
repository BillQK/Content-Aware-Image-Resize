#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>

#include "Image_test_helpers.h"
#include "Matrix.hpp"
#include "unit_test_framework.h"

using namespace std;

// Here's a free test for you! Model yours after this one.
// Add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image::print produces the correct output.

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Image_test_helpers.h as needed.

// Test that the default constructor has the correct dimensions
TEST(test_default_constructor) {
  Image img;
  ASSERT_EQUAL(img.get_height(), 0);
  ASSERT_EQUAL(img.get_width(), 0);
}

// Test that the constructor has the correct dimensions
// and each pixel is initialized to 0
TEST(test_constructor) {
  Image img(10, 20);
  ASSERT_EQUAL(img.get_height(), 20);
  ASSERT_EQUAL(img.get_width(), 10);
  for (int row = 0; row < img.get_height(); ++row) {
    for (int col = 0; col < img.get_width(); ++col) {
      ASSERT_EQUAL(img.get_pixel(row, col).r, 0);
      ASSERT_EQUAL(img.get_pixel(row, col).g, 0);
      ASSERT_EQUAL(img.get_pixel(row, col).b, 0);
    }
  }
}

// Test that the fill constructor has the correct dimensions
// and each pixel is initialized to the given color
TEST(test_fill_constructor) {
  Image img(10, 20, Pixel{100, 200, 150});
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      Pixel p = img.get_pixel(i, j);
      ASSERT_EQUAL(p.r, 100);
      ASSERT_EQUAL(p.g, 200);
      ASSERT_EQUAL(p.b, 150);
    }
  }
}

// Reads the given ppm file and checks
// that readppm is reading the file correctly
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
}

// Testing readppm with an input stream instead of a file
// checking that it's reading the input correctly
TEST(test_readppm_stream) {
  string in = "P3 \n2 2 \n255 \n1 1 2 \n2 2 2 \n3 3 2 \n4 4 4 \n";
  std::istringstream in_stream(in);
  Image img = Image::read_ppm(in_stream);

  string correct_out = "P3\n2 2\n255\n1 1 2 2 2 2 \n3 3 2 4 4 4 \n";
  std::ostringstream out_stream;
  img.print(out_stream);
  string actual = out_stream.str();
  std::cout << actual << std::endl;
  ASSERT_EQUAL(actual, correct_out);
}

// Testing readppm with a stream instead of a file
// checking that it's reading the input correctly
TEST(test_read_ppm) {
  std::stringstream ss;
  ss << "P3" << std::endl;
  ss << "3 2" << std::endl;
  ss << "255" << std::endl;
  ss << "255 0 0" << std::endl;
  ss << "0 255 0" << std::endl;
  ss << "0 0 255" << std::endl;
  ss << "255 255 0" << std::endl;
  ss << "255 0 255" << std::endl;
  ss << "0 255 255" << std::endl;

  Image img = Image::read_ppm(ss);

  ASSERT_EQUAL(img.get_width(), 3);
  ASSERT_EQUAL(img.get_height(), 2);

  Pixel p1 = img.get_pixel(0, 0);
  ASSERT_EQUAL(p1.r, 255);
  ASSERT_EQUAL(p1.g, 0);
  ASSERT_EQUAL(p1.b, 0);

  Pixel p2 = img.get_pixel(0, 1);
  ASSERT_EQUAL(p2.r, 0);
  ASSERT_EQUAL(p2.g, 255);
  ASSERT_EQUAL(p2.b, 0);

  Pixel p3 = img.get_pixel(0, 2);
  ASSERT_EQUAL(p3.r, 0);
  ASSERT_EQUAL(p3.g, 0);
  ASSERT_EQUAL(p3.b, 255);

  Pixel p4 = img.get_pixel(1, 0);
  ASSERT_EQUAL(p4.r, 255);
  ASSERT_EQUAL(p4.g, 255);
  ASSERT_EQUAL(p4.b, 0);

  Pixel p5 = img.get_pixel(1, 1);
  ASSERT_EQUAL(p5.r, 255);
  ASSERT_EQUAL(p5.g, 0);
  ASSERT_EQUAL(p5.b, 255);

  Pixel p6 = img.get_pixel(1, 2);
  ASSERT_EQUAL(p6.r, 0);
  ASSERT_EQUAL(p6.g, 255);
  ASSERT_EQUAL(p6.b, 255);
}

// Checking that get_width returns the correct width
// with different Image constructors
TEST(test_get_width) {
  Image img = Image();
  ASSERT_EQUAL(img.get_width(), 0);
  Image img1 = Image(0, 0);
  ASSERT_EQUAL(img1.get_width(), 0);
  Image img2 = Image(4, 5);
  ASSERT_EQUAL(img2.get_width(), 4);
  Image img3 = Image(5, 5, Pixel{255, 255, 255});
  ASSERT_EQUAL(img3.get_width(), 5);
}

// Checking that get_height returns the correct height
// with different Image constructors
TEST(test_get_height) {
  Image img = Image();
  ASSERT_EQUAL(img.get_height(), 0);
  Image img1 = Image(0, 0);
  ASSERT_EQUAL(img1.get_height(), 0);
  Image img2 = Image(4, 5);
  ASSERT_EQUAL(img2.get_height(), 5);
  Image img3 = Image(5, 4, Pixel{255, 255, 255});
  ASSERT_EQUAL(img3.get_height(), 4);
}

// Checking that it's getting the correct pixel color
// at the given row and col
TEST(test_get_pixel) {
  string filename = "dog_4x5.correct.ppm";
  ifstream file(filename);

  Image img;
  img = img.read_ppm(file);

  Pixel pix = img.get_pixel(1, 0);
  Pixel correct_pix = Pixel{255, 255, 250};
  ASSERT_EQUAL(pix.b, correct_pix.b);
  ASSERT_EQUAL(pix.g, correct_pix.g);
  ASSERT_EQUAL(pix.r, correct_pix.r);
}

// Sets a pixel in the image to be white
// checks if the pixel color was switched
TEST(test_set_pixel) {
  // before set_pixel
  string filename = "dog_4x5.correct.ppm";
  ifstream file(filename);

  Image img;
  img = img.read_ppm(file);

  Pixel pix = img.get_pixel(1, 0);
  Pixel white_pix = Pixel{255, 255, 250};
  ASSERT_EQUAL(white_pix.r, pix.r);
  ASSERT_EQUAL(white_pix.g, pix.g);
  ASSERT_EQUAL(white_pix.b, pix.b);

  // after set_pixel
  Pixel new_pix = Pixel{0, 0, 250};
  img.set_pixel(1, 0, new_pix);
  pix = img.get_pixel(1, 0);

  ASSERT_EQUAL(new_pix.r, pix.r);
  ASSERT_EQUAL(new_pix.g, pix.g);
  ASSERT_EQUAL(new_pix.b, pix.b);
}

// This is some macro magic that adds a main() function that runs the test cases
// defined in this file. Do not add your own main() function.
TEST_MAIN()
