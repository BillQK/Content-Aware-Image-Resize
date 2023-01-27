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
    // Read the first line - P3 (indicates it's a "Plain PPM file")
    // Read the width and height (seperated by spaces)
    // read is stream then store it in the channel array, accordingly. 

    // getting width & height
    string trash; // q: how to skip the words that i don't need word ?
    is >> trash; // P3
    int width;
    is >> width;
    int height;
    is >> height;
    is >> trash; // max value 

    Image img(width, height);
    cout<<img.get_width()<<"height"<<endl;

    ostringstream output;
    img.m_red_channel.print(output);
/*
4 width, 5 height
(0 0 0) (255 255 250) (0 0 0)  (0 0 0)
 0 1 2    3   4   5    6 7 8   9 10 11
 r g b    r   g   b    r g b   r  g  b
*/
    for(int row=0; row<width; row++) {
        for(int col=0; col<height; col++) {
            img.m_red_channel.at(row, col) = is.get();
            img.m_green_channel.at(row, col) = is.get();
            img.m_blue_channel.at(row, col) = is.get();
        }
    }
    // cout<<"loops done"<<endl;

    // while loop, couldn't get the math 

    // while(is) {
    //     cout << color;
    //     color=is.get();
    //     // if (color == "\n") {
    //     //     cout << "newline " << endl;
    //     // }
    // }
    // cout << img.m_width << "width" << endl;

    // stack overflow code sample
    // char c;
    // c = is.get();
    // while (is)
    // {
    //     cout << c;
    //     c = is.get();
    // }

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

