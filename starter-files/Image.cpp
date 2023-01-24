#include <iostream>

#include "Image.hpp" 

using namespace std;

Image::Image(): m_width(0), m_height(0) {}


Image::Image(int width, int height): Image{width, height, Pixel{0,0,0}} {}

Image::Image(int width, int height, const Pixel& fill) : m_width(width), m_height(height) {
    m_red_channel = Matrix(width, height, fill.r);
    m_green_channel = Matrix(width, height, fill.g);
    m_blue_channel = Matrix(width, height, fill.b);
}

Image Image::read_ppm(std::istream& is) {} 

void Image::print(std::ostream& os) const {} 

int Image::get_width() const { return m_width; }

int Image::get_height() const { return m_height; }

Pixel Image::get_pixel(int row, int column) const {
    int r = m_red_channel.at(row, column);
    int g = m_green_channel.at(row, column);
    int b = m_blue_channel.at(row, column);
    return Pixel{r, g, b};
}

void Image::set_pixel(int row, int column, const Pixel& color) {
    // modify the color matrix to contain the new color
    m_red_channel.at(row, column) = color.r;
    m_green_channel.at(row, column) = color.g;
    m_blue_channel.at(row, column) = color.b;
}

