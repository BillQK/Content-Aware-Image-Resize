#include "Matrix.hpp"
#include "Image_test_helpers.h"
#include "unit_test_framework.h"
#include <iostream>
#include <string>
#include <sstream>
#include <istream>
#include <fstream>

using namespace std;

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Image_test_helpers.h as needed.
TEST(test_default_constructor)
{
  Image img;
  ASSERT_EQUAL(img.get_height(), 0);
  ASSERT_EQUAL(img.get_width(), 0);
}

TEST(test_constructor)
{
  Image img(10, 20);
  ASSERT_EQUAL(img.get_height(), 20);
  ASSERT_EQUAL(img.get_width(), 10);
}

TEST(test_fill_constructor)
{
  Image img(10, 20, Pixel{100, 200, 150});
  for (int i = 0; i < 20; i++)
  {
    for (int j = 0; j < 10; j++)
    {
      Pixel p = img.get_pixel(i, j);
      ASSERT_EQUAL(p.r, 100);
      ASSERT_EQUAL(p.g, 200);
      ASSERT_EQUAL(p.b, 150);
    }
  }
}

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

    ASSERT_EQUAL(img.get_width() , 3);
    ASSERT_EQUAL(img.get_height(), 2);

    Pixel p1 = img.get_pixel(0, 0);
    ASSERT_EQUAL(p1.r , 255);
    ASSERT_EQUAL(p1.g , 0);
    ASSERT_EQUAL(p1.b , 0);

    Pixel p2 = img.get_pixel(0, 1);
    ASSERT_EQUAL(p2.r , 0);
    ASSERT_EQUAL(p2.g , 255);
    ASSERT_EQUAL(p2.b , 0);

    Pixel p3 = img.get_pixel(0, 2);
    ASSERT_EQUAL(p3.r , 0);
    ASSERT_EQUAL(p3.g , 0);
    ASSERT_EQUAL(p3.b , 255);

    Pixel p4 = img.get_pixel(1, 0);
    ASSERT_EQUAL(p4.r , 255);
    ASSERT_EQUAL(p4.g , 255);
    ASSERT_EQUAL(p4.b , 0);

    Pixel p5 = img.get_pixel(1, 1);
    ASSERT_EQUAL(p5.r , 255);
    ASSERT_EQUAL(p5.g , 0);
    ASSERT_EQUAL(p5.b , 255);

    Pixel p6 = img.get_pixel(1, 2);
    ASSERT_EQUAL(p6.r , 0);
    ASSERT_EQUAL(p6.g , 255);
    ASSERT_EQUAL(p6.b , 255);
}

TEST(test_readppm)
{

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

TEST(test_get_width)
{
  Image img = Image(4, 5);
  ASSERT_EQUAL(img.get_width(), 4);
}

TEST(test_get_height)
{
  Image img = Image(4, 5);
  ASSERT_EQUAL(img.get_height(), 5);
}

TEST(test_get_pixel)
{
  Image img = Image(4, 5);
  Pixel p = img.get_pixel(0, 0);
  Pixel a = Pixel{0, 0, 0};
  ASSERT_EQUAL(p.b, a.b);
  ASSERT_EQUAL(p.g, a.g);
  ASSERT_EQUAL(p.r, a.r);
}

TEST(test_set_pixel)
{
  Pixel p = Pixel{255, 255, 250};
  Image img = Image(4, 5);
  img.set_pixel(2, 3, p);
  Pixel a = img.get_pixel(0, 0);
  Pixel b = img.get_pixel(2, 3);

  ASSERT_NOT_EQUAL(p.r, a.r);
  ASSERT_NOT_EQUAL(p.g, a.g);
  ASSERT_NOT_EQUAL(p.b, a.b);

  ASSERT_EQUAL(p.r, b.r);
  ASSERT_EQUAL(p.g, b.g);
  ASSERT_EQUAL(p.b, b.b);
}




// This is some macro magic that adds a main() function that runs the test cases
// defined in this file. Do not add your own main() function.
TEST_MAIN()
