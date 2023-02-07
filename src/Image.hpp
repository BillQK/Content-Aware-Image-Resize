#ifndef IMAGE_H
#define IMAGE_H

/* Image.hpp
 *
 * DO NOT MODIFY THIS FILE
 *
 * Adapted by James Perretta at Northeastern University, Spring 2023.
 * Originally written by James Juett at the University of Michigan
 * for project 3 in EECS 280, Winter 2016.
 */

// Contains declarations (not definitions!) for the iostream library. You will need
// to include iostream in Image.cpp.
#include <iosfwd>

#include "Matrix.hpp"

// Representation of an RGB Pixel used for
// parameter passing and returns by the
// Image module. This is a POD type.
struct Pixel {
  int r;
  int g;
  int b;
};

const int c_max_intensity = 255;

// Representation of 2D RGB image in PPM format.
// The "final" keyword prevents inheriting from this class.
class Image final {
public:
  // Initializes an empty image
  Image();

  // Initializes an Image with the given dimensions and
  // with each pixel initialized to "zero" in each channel.
  Image(int width, int height);

  // Initializes an Image with the given dimensions and
  // with each pixel initialized to the value specified by "fill".
  Image(int width, int height, const Pixel& fill);

  // Reads an image in PPM format (without comments, any kind of whitespace is ok)
  // from the given input stream, constructs an Image object according to the data,
  // and returns it.
  // Note: Static member functions are called *without* an object of
  // the class. See Image_public_test.cpp for an example of how to use
  // this function.
  static Image read_ppm(std::istream& is);

  // Writes this image to the given output stream in PPM format.
  // You must use the kind of whitespace specified here.
  // First, prints out the header for the image like this:
  //   P3 [newline]
  //   WIDTH [space] HEIGHT [newline]
  //   255 [newline]
  // Next, prints out the rows of the image, each followed by a
  // newline. Each pixel in a row is printed as three ints
  // for its red, green, and blue components, in that order. Each
  // int is followed by a space. This means that there will be an
  // "extra" space at the end of each line. See the project spec
  // for an example.
  void print(std::ostream& os) const;

  // Returns the width of this Image.
  int get_width() const;

  // Returns the height of this Image.
  int get_height() const;

  // Returns the pixel at the given row and column.
  // If row or column are out of bounds (either less than zero or row >= height
  // or column >= width, the behavior is undefined.
  Pixel get_pixel(int row, int column) const;

  // Sets the pixel in this Image at the given row and column to the given color.
  // If row or column are out of bounds (either less than zero or row >= height
  // or column >= width, the behavior is undefined.
  void set_pixel(int row, int column, const Pixel& color);

private:
  int m_width;
  int m_height;
  Matrix m_red_channel;
  Matrix m_green_channel;
  Matrix m_blue_channel;
};

#endif // IMAGE_H
