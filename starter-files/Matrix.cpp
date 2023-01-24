#include "Matrix.hpp"

// Initializes an empty Matrix
Matrix::Matrix() {

}
 // Initializes a Matrix with the given dimensions and
  // with each cell initialized to zero.
Matrix::Matrix(int width, int height): m_width(width), m_height(height){}


 // Initializes a Matrix with the given dimensions and
  // with each cell initialized to the value specified by fill_value.
Matrix::Matrix(int width, int height, int fill_value): m_width(width), m_height(height){
    // for(int i = 0; i < height * width; ++i){
    //     m_data[i] = fill_value;
    // }
}


int Matrix::get_width() const {
    return m_width;
}

int Matrix::get_height() const {
    return m_height;
}

int& Matrix::at(int row, int column) {
    return m_data[row*column];
}

const int& Matrix::at(int row, int column) const {
    return m_data[row*column];
}

void Matrix::print(std::ostream& os) const {
    
}
