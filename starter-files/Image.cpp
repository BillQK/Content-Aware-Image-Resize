#include <iostream>
#include <fstream>
#include <sstream>

#include "Image.hpp" 

using namespace std;

Image::Image(): m_width(0), m_height(0) {}


Image::Image(int width, int height): Image{width, height, Pixel{0,0,0}} {}

Image::Image(int width, int height, const Pixel& fill): m_width(width), m_height(height) {
    m_red_channel = Matrix(width, height, fill.r);
    m_green_channel = Matrix(width, height, fill.g);
    m_blue_channel = Matrix(width, height, fill.b);
}

Image Image::read_ppm(std::istream& is) {
    // getting width & height
    string trash; // q: how to skip the words that i don't need word ?
    is >> trash; // P3
    int width;
    is >> width;
    int height;
    is >> height;
    is >> trash; // max value 

    Image img(width, height);
    cout<<img.get_width()<<"weight"<<endl;

    ostringstream output;
    img.m_red_channel.print(output);

    int color;
/*
4 width, 5 height
(0 0 0) (255 255 250) (0 0 0)  (0 0 0)
 0 1 2    3   4   5    6 7 8   9 10 11
 r g b    r   g   b    r g b   r  g  b
*/
    for(int row=0; row<width; row++) {
        for(int col=0; col<height; col++) {
            is>>color;
            img.m_red_channel.at(row, col) = color;
            is>>color;
            img.m_green_channel.at(row, col) = color;
            is>>color;
            img.m_blue_channel.at(row, col) = color;
        }
    }

    for(int row=0; row<width; row++) {
        for(int col=0; col<height; col++) {
            cout<< row << img.m_green_channel.at(row,col)<<" RED"<<endl;
        }
    }

    // cout<<img.m_red_channel<<" REDD"<<endl;
    // cout<<img.m_green_channel.at(0,1)<<" GREN"<<endl;
    // cout<<img.m_blue_channel.at(0,1)<<" BLUE"<<endl;

    // cout<<img.m_red_channel.at(0,2)<<" REDD"<<endl;
    // cout<<img.m_green_channel.at(0,2)<<" GREN"<<endl;
    // cout<<img.m_blue_channel.at(0,2)<<" BLUE"<<endl;

    // return the saved image with dimensions & colors
    return img;
} 

void Image::print(std::ostream& os) const {
    os << "P3" << endl;
    os << get_width() << " " << get_height() << endl;
    os << c_max_intensity << endl;
    // print pixel
    for(int row=0;row<m_height; row++) {
        for(int col=0; col<m_width; col++) {
            // q: do i flush w/ ends? tests doesn't pass then
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
    // modify the color matrix to contain the new color
    m_red_channel.at(row, column) = color.r;
    m_green_channel.at(row, column) = color.g;
    m_blue_channel.at(row, column) = color.b;
}

