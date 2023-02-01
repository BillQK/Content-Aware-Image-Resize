#include <iostream>
#include <cassert>

#include "processing.hpp"

using namespace std;

namespace
{
  // The implementation of squared_difference is provided for you.
  int squared_difference(Pixel p1, Pixel p2);
}

// Implement the functions declared in processing.hpp here.

namespace
{
  // The implementation of squared_difference is provided for you.
  int squared_difference(Pixel p1, Pixel p2)
  {
    int dr = p2.r - p1.r;
    int dg = p2.g - p1.g;
    int db = p2.b - p1.b;
    // Divide by 100 is to avoid possible overflows
    // later on in the algorithm.
    return (dr * dr + dg * dg + db * db) / 100;
  }
}

// Returns a copy of the given image that is rotated 90 degrees to the
// left (counterclockwise).
Image rotate_left(const Image &img)
{
  int new_width = img.get_height();
  int new_height = img.get_width();
  Image new_img = Image{new_width, new_height};
  for (int row = 0; row < new_height; ++row)
  {
    for (int col = 0; col < new_width; ++col)
    {
      Pixel from_pixel = img.get_pixel(col, img.get_width() - 1 - row);
      new_img.set_pixel(row, col, from_pixel);
    }
  }
  return new_img;
}
// Returns a copy of the given image that is rotated 90 degrees to the
// right (clockwise).
Image rotate_right(const Image &img)
{
  int new_width = img.get_height();
  int new_height = img.get_width();
  Image new_image = Image(new_width, new_height);
  for (int row = 0; row < new_height; ++row)
  {
    for (int col = 0; col < new_width; ++col)
    {
      Pixel from_pixel = img.get_pixel(img.get_height() - 1 - col, row);
      new_image.set_pixel(row, col, from_pixel);
    }
  }
  return new_image;
}

// Returns the energy Matrix computed from the given Image.
// See the assignment spec for details on computing the energy matrix.
Matrix compute_energy_matrix(const Image &img)
{
  Matrix energy_mat = Matrix{img.get_width(), img.get_height()};
  int max_energy = 0;
  // fills middle
  for (int row = 1; row < energy_mat.get_height() - 1; ++row)
  {
    for (int col = 1; col < energy_mat.get_width() - 1; ++col)
    {
      Pixel n = img.get_pixel(row - 1, col);
      Pixel s = img.get_pixel(row + 1, col);
      Pixel w = img.get_pixel(row, col - 1);
      Pixel e = img.get_pixel(row, col + 1);
      energy_mat.at(row, col) = squared_difference(n, s) + squared_difference(w, e);
      int energy_x = energy_mat.at(row, col);
      max_energy = std::max(energy_x, max_energy);
    }
  }
  // fill border
  for (int row = 0; row < energy_mat.get_height(); ++row)
  {
    energy_mat.at(row, 0) = max_energy;
    energy_mat.at(row, energy_mat.get_width() - 1) = max_energy;
  }

  for (int col = 0; col < energy_mat.get_width(); ++col)
  {
    energy_mat.at(0, col) = max_energy;
    energy_mat.at(energy_mat.get_height() - 1, col) = max_energy;
  }
  return energy_mat;
}

// Returns the vertical cost Matrix computed from the given Image.
// See the assignment spec for details on computing the cost matrix.
Matrix compute_vertical_cost_matrix(const Image &img)
{
  Matrix energy_mat = compute_energy_matrix(img);
  Matrix vertical_cost = Matrix{img.get_width(), img.get_height()};
  // first row
  for (int col = 0; col < vertical_cost.get_width(); ++col)
  {
    vertical_cost.at(0, col) = energy_mat.at(0, col);
  }
  // remaining rows
  for (int row = 1; row < vertical_cost.get_height(); ++row)
  {
    for (int col = 0; col < vertical_cost.get_width(); ++col)
    {
      int min_energy = 0;
      int center = vertical_cost.at(row - 1, col);
      // left border
      if (col == 0)
      {
        int east = vertical_cost.at(row - 1, col + 1);
        min_energy = min(center, east);
      }
      // right border
      else if (col == vertical_cost.get_width() - 1)
      {
        int west = vertical_cost.at(row - 1, col - 1);
        min_energy = min(west, center);
      }
      // everything else
      else
      {
        int west = vertical_cost.at(row - 1, col - 1);
        int east = vertical_cost.at(row - 1, col + 1);
        min_energy = min(west, min(center, east));
      }
      vertical_cost.at(row, col) = energy_mat.at(row, col) + min_energy;
    }
  }
  return vertical_cost;
}
// Returns a vector containing the column indices of each pixel along the
// vertical seam with the minimal cost according to the given cost matrix.
// The elements in the vector starts with the lowest numbered row (top of image)
// and progressing to the highest (bottom of image).
// While determining the seam, if any pixels tie for lowest cost, the leftmost
// one (i.e. with the lowest column number) is used.
// See the project spec for details on computing the minimal seam.
std::vector<int> find_minimal_vertical_seam(const Matrix &cost)
{
  vector<int> min_vect;
  int min_index = 0; // min_index does not need to be reset, value needs to be carried over
  int min_cost;
  for(int row=cost.get_height()-1; row>0; --row) {
    // if row = bottom row: find the minimum cost
    if(row==cost.get_height()-1) {
      min_cost = cost.at(row,0); // min cost is set to the first value of the row
      for(int col=0; col<cost.get_width(); ++col) {
        if(cost.at(row, col) < min_cost && cost.at(row, col) != min_cost) {
          min_cost = cost.at(row, col);
          min_index = col;
        }
      }
      min_vect.push_back(min_index);
    }
      // look for minimum in the slices above
        // left border
        if (min_index == 0)
        {
          Matrix::Slice s = cost.get_row_slice(row - 1, min_index, min_index + 1); // middle & right col
          // if(data.at(0) <= data.at(1)){
          //   min_index = min_index;
          // }
          if(s.data.at(0) > s.data.at(1)) {
            min_index = min_index+1;
          }
        }
        // right border
        else if (min_index == cost.get_width() - 1)
        {
          Matrix::Slice s = cost.get_row_slice(row - 1, min_index - 1, min_index); // left & middle col
          vector<int> data = s.data;

          if (data.at(0) <= data.at(1))
          {
            min_index = min_index - 1;
          }
        }
        // everything else
        else{
          Matrix::Slice s = cost.get_row_slice(row-1, min_index-1, min_index+1);
          // cout << s.row << endl;
          // cout << s.col_start << endl;
          // cout << s.col_end << endl;
          // cout << "data"<<s.data.at(0) <<" " <<s.data.at(1)<<" "<<s.data.at(2)<<" minindex"<<min_index<< endl;

          min_cost = min(s.data.at(0), min(s.data.at(1), s.data.at(2)));

          if(min_cost == s.data.at(0)){
            min_index = min_index-1;
          }
          else if(min_cost == s.data.at(2)){
            min_index = min_index+1;
          }
          // cout<<"min"<<min_cost<<" minindex"<<min_index<<endl;
        }
        // min_cost = cost.at(row-1, min_index);
      //   cout<<"min cost: "<<min_cost<<" min index: "<<min_index<<endl;
      // cout <<"row: " << row <<" "<< "min index: "<<min_index << endl;
    min_vect.push_back(min_index);
  }
  vector<int> reversed_vect;
  
  int iterator = min_vect.size()-1;
  for(size_t i=0; i<min_vect.size(); ++i){
    reversed_vect.push_back(min_vect.at(iterator));
    // cout << min_vect.at(i) << endl;
    iterator--;
  }
  return reversed_vect;
}

// Returns a copy of img with the given vertical seam removed. That is, one
// pixel will be removed from every row in the image. The pixel
// removed from row r will be the one with column equal to seam[r].
// The width of the image will be one less than before.
// See the project spec for details on removing a vertical seam.
Image remove_vertical_seam(const Image &img, const std::vector<int> &seam)
{
  Image new_img = Image(img.get_width() - 1, img.get_height());

  Matrix vertical_cost = compute_vertical_cost_matrix(img);
  vector<int> min_seam = find_minimal_vertical_seam(vertical_cost);

  for(int row=0; row<img.get_height(); ++row){
    int new_col=0;
    for(int col=0; col<img.get_width(); ++col){
      // if column = minimum seam, skip column
      // compare column to min_seam(row), see if that's the col that needs to be taken out
      // if(col == min_seam.at(row)) {
        // do nothing
      // }
      if(col != min_seam.at(row)) {
        Pixel curr_pix = img.get_pixel(row,col);
        new_img.set_pixel(row,new_col,curr_pix);
        new_col++;
      }
    }
  }
  return new_img;
}

// Returns a copy of img with its width reduced to be new_width by using
// the seam carving algorithm. See the spec for details.
// Requires that 0 < new_width <= img.get_width(), otherwise the behavior
// is undefined.
Image seam_carve_width(const Image& img, int new_width){
  assert(0<new_width);
  assert(new_width <= img.get_width());

  Image new_img = img;
  // loop until cut down to desired width
  while(new_img.get_width() != new_width) {
    // cout<<"width"<<new_img.get_width()<<endl;
    // cout<<"new width"<<new_width<<endl;
    Matrix energy_matrix = compute_energy_matrix(new_img);
    Matrix cost_matrix = compute_vertical_cost_matrix(new_img);
    vector<int> minimal_cost_seam = find_minimal_vertical_seam(cost_matrix);
    new_img = remove_vertical_seam(new_img, minimal_cost_seam);
    // cout<<"carved width"<<new_img.get_width()<<endl;
  }
  
  return new_img;
}

// Returns a copy of img with its height reduced to be new_height by using
// the seam carving algorithm. See the spec for details.
// Requires that 0 < new_height <= img.get_height(), otherwise the behavior
// is undefined.
Image seam_carve_height(const Image& img, int new_height){
  assert(0<new_height);
  assert(new_height<=img.get_height());

  Image new_image = rotate_left(img); 
  new_image = seam_carve_width(new_image, new_height); 
  new_image = rotate_right(new_image);
  return new_image;
}

// Returns a copy of img with its width and height reduced to be
// new_width and new_height, respectively.
//
// NOTE: This is equivalent to applying seam_carve_width(img, new_width)
// and then applying seam_carve_height(img, new_height).

// Requires that 0 < new_height <= img.get_height() and
// 0 < new_height <= img.get_height(), otherwise the behavior
// is undefined.
Image seam_carve(const Image &img, int newWidth, int newHeight)
{
  Image new_img = seam_carve_width(img, newWidth);
  new_img = seam_carve_height(img, newHeight);
  return new_img;
}
