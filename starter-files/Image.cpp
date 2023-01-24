#include "Image.hpp" 

Image::Image() {}
Image::Image(int width, int height) : m_width(width), m_height(height){}
Image::Image(int width, int height, const Pixel& fill) : m_width(width), m_height(height) {}

// static Image::read_ppm(std::istream& is){} 


// void Image::print(std::ostream& os) {} 

int Image::get_width() const { return m_width; }

int Image::get_height() const { return m_height; }

Pixel Image::get_pixel(int row, int column) const { }

void Image::set_pixel(int row, int column, const Pixel& color) {}

