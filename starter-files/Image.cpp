#include <iostream>
#include <fstream>
#include <sstream>

#include "Image.hpp" 

using namespace std;

Image::Image(): m_width(0), m_height(0) {}


Image::Image(int width, int height): m_width(width), m_height(height) {
    m_red_channel = Matrix(width, height, 0);
    m_green_channel = Matrix(width, height, 0);
    m_blue_channel = Matrix(width, height, 0);
}

Image::Image(int width, int height, const Pixel& fill): m_width(width), m_height(height) {
    m_red_channel = Matrix(width, height, fill.r);
    m_green_channel = Matrix(width, height, fill.g);
    m_blue_channel = Matrix(width, height, fill.b);
}

Image Image::read_ppm(std::istream& is) {
    // getting width & height
    int width; 
    int height; 
    string filetype; 
    string newLine;
    int color_max; 

    // filetype = is.get();
    // newLine = is.get(); //
    // width = is.get(); //
    // height = is.get(); 
    // newLine = is.get(); 
    // color_max = is.get(); 

    is >> filetype; 
    cout << filetype << endl;
    is >> width; 
    cout << width << endl; 
    is >> height; 
    cout << height << endl;


    
    // is.get() >> height >> width >> newLine; //

    // is.get() >> intensity >> newLine; ////

    Image img = Image(width, height);

    int color;
    for(int row=0; row<width; row++) {
        for(int col=0; col<height; col++) {
            if (is.peek() != '\n') {
                is>>color;
                img.m_red_channel.at(row, col) = color;
                is>>color;
                img.m_green_channel.at(row, col) = color;
                is>>color;
                img.m_blue_channel.at(row, col) = color;
            }
            else { 
                getline(is, newLine);
            }
        }
        
    }


    return img; 

    // cout<<img.m_red_channel<<" REDD"<<endl;
    // cout<<img.m_green_channel.at(0,1)<<" GREN"<<endl;
    // cout<<img.m_blue_channel.at(0,1)<<" BLUE"<<endl;

    // cout<<img.m_red_channel.at(0,2)<<" REDD"<<endl;
    // cout<<img.m_green_channel.at(0,2)<<" GREN"<<endl;
    // cout<<img.m_blue_channel.at(0,2)<<" BLUE"<<endl;

    // return the saved image with dimensions & colors
} 

void Image::print(std::ostream& os) const {
    os << "P3" << endl;
    os << m_width << " " << m_height << endl;
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

