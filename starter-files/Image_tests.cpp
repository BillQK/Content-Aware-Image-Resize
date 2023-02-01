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
