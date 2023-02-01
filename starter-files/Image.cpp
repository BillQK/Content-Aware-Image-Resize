#include "Image.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

Image::Image() : m_width(0), m_height(0) {}

Image::Image(int width, int height) : m_width(width), m_height(height) {
  m_red_channel = Matrix(width, height, 0);
  m_green_channel = Matrix(width, height, 0);
  m_blue_channel = Matrix(width, height, 0);
}

Image::Image(int width, int height, const Pixel& fill) : m_width(width), m_height(height) {
  m_red_channel = Matrix(width, height, fill.r);
  m_green_channel = Matrix(width, height, fill.g);
  m_blue_channel = Matrix(width, height, fill.b);
}

Image Image::read_ppm(std::istream& is) {
  string magic_number;
  int width, height, max_color;
  is >> magic_number >> width >> height >> max_color;

  Image img = Image(width, height);

  for (int row = 0; row < img.get_height(); row++) {
    for (int col = 0; col < img.get_width(); col++) {
      int red, green, blue;
      is >> red >> green >> blue;
      Pixel p = Pixel{red, green, blue};
      img.set_pixel(row, col, p);
    }
  }
  return img;
}

void Image::print(std::ostream& os) const {
  os << "P3" << endl;
  os << m_width << " " << m_height << endl;
  os << c_max_intensity << endl;
  // print pixel
  for (int row = 0; row < m_height; row++) {
    for (int col = 0; col < m_width; col++) {
      os << m_red_channel.at(row, col) << " ";
      os << m_green_channel.at(row, col) << " ";
      os << m_blue_channel.at(row, col) << " ";
    }
    os << endl;
  }
}

int Image::get_width() const { return m_width; }

int Image::get_height() const { return m_height; }

Pixel Image::get_pixel(int row, int column) const {
  int r = m_red_channel.at(row, column);
  int g = m_green_channel.at(row, column);
  int b = m_blue_channel.at(row, column);
  return Pixel{r, g, b};
}

void Image::set_pixel(int row, int column, const Pixel& color) {
  m_red_channel.at(row, column) = color.r;
  m_green_channel.at(row, column) = color.g;
  m_blue_channel.at(row, column) = color.b;
}
