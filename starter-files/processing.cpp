// #include <algorithm>

#include "processing.hpp"

// using namespace std;

namespace {
  // The implementation of squared_difference is provided for you.
  int squared_difference(Pixel p1, Pixel p2);
}

// Implement the functions declared in processing.hpp here.

namespace {
  // The implementation of squared_difference is provided for you.
  int squared_difference(Pixel p1, Pixel p2) {
    int dr = p2.r - p1.r;
    int dg = p2.g - p1.g;
    int db = p2.b - p1.b;
    // Divide by 100 is to avoid possible overflows
    // later on in the algorithm.
    return (dr*dr + dg*dg + db*db) / 100;
  }
}

// Returns a copy of the given image that is rotated 90 degrees to the
// left (counterclockwise).
Image rotate_left(const Image& img) {
  int new_width = img.get_height();
  int new_height = img.get_width();
  Image new_img = Image{new_width, new_height};
  for(int row=0; row<new_height; ++row) {
    for(int col=0; col<new_width; ++col) {
      Pixel from_pixel = img.get_pixel(col, img.get_width()-1-row);
      new_img.set_pixel(row, col, from_pixel);
    }
  }
  return new_img;
}
// Returns a copy of the given image that is rotated 90 degrees to the
// right (clockwise).
Image rotate_right(const Image& img) {
  int new_width = img.get_height(); 
  int new_height = img.get_width();
  Image new_image = Image(new_width, new_height); 
  for (int row = 0; row < new_height; ++row) {
    for (int col = 0; col < new_width; ++col) {
      Pixel from_pixel = img.get_pixel(img.get_height()-1-col,row);
      new_image.set_pixel(row,col,from_pixel);
    }
  }
  return new_image;
}

// Returns the energy Matrix computed from the given Image.
// See the assignment spec for details on computing the energy matrix.
Matrix compute_energy_matrix(const Image& img) {
  Matrix energy_mat = Matrix{img.get_height(), img.get_width()};
  int max_energy = 0;
  // fills middle
  for(int row=1; row<energy_mat.get_height()-1; ++row) {
    for(int col=1; col<energy_mat.get_width()-1; ++col) {
      Pixel n=img.get_pixel(row-1, col);
      Pixel s=img.get_pixel(row+1, col);
      Pixel w = img.get_pixel(row, col-1); 
      Pixel e = img.get_pixel(row, col+1);
      energy_mat.at(row, col) = squared_difference(n,s) + squared_difference(w,e);
      int energy_x = energy_mat.at(row, col);
      max_energy = std::max(energy_x, max_energy);
    }
  }
  // fill border
  for(int row = 0; row< energy_mat.get_height(); ++row){ 
    energy_mat.at(row,0) = max_energy; 
    energy_mat.at(row,energy_mat.get_width()-1) = max_energy;
  }

  for(int col = 0; col< energy_mat.get_width(); ++col) {
    energy_mat.at(0,col) = max_energy; 
    energy_mat.at(energy_mat.get_height()-1,col) = max_energy;
  }
  return energy_mat;
}

// Returns the vertical cost Matrix computed from the given Image.
// See the assignment spec for details on computing the cost matrix.
Matrix compute_vertical_cost_matrix(const Image& img) {
  Matrix energy_mat = compute_energy_matrix(img); 
  Matrix vertical_cost = Matrix{img.get_height(), img.get_width()};
  // first row
  for(int col=0; col<vertical_cost.get_width(); ++col) {
    vertical_cost.at(0,col) = energy_mat.at(0,col);
  }
  // remaining rows
  for (int row = 1; row < vertical_cost.get_height(); ++row) {
    for (int col = 0; col < vertical_cost.get_width(); ++col){
      // left border
      if(col==0) {
        int energy_center = energy_mat.at(row-1,col);
        int energy_east = energy_mat.at(row-1, col+1);
        int min_energy = energy_mat.at(row,col) + std::min(energy_center, energy_east);
        vertical_cost.at(row,col) += min_energy; 
      }
      // right border
      else if(col==vertical_cost.get_width()-1) {
        int energy_west = energy_mat.at(row-1,col-1);
        int energy_center = energy_mat.at(row-1,col);
        int min_energy = energy_mat.at(row,col) +  std::min(energy_west, energy_center);
        vertical_cost.at(row,col) += min_energy; 
      }
      // everything else
      else {
        int energy_west = energy_mat.at(row-1,col-1);
        int energy_center = energy_mat.at(row-1,col); 
        int energy_east = energy_mat.at(row-1, col+1); 
        int min_energy =  energy_mat.at(row,col) + std::min(energy_center, std::min(energy_west, energy_east));
        vertical_cost.at(row,col) += min_energy; 
      }
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
std::vector<int> find_minimal_vertical_seam(const Matrix& cost){ 
  std::vector<int> min_vect;
  int min_col = 0; // min_col does not need to be reset, value needs to be carried over
  for(int row=cost.get_height(); row>0; --row) {
    // values reset every new row
    int min_cost = 0;
    for(int col=0; col<cost.get_width(); ++row) {
      // bottom row: find the minimum cost
      if(row==cost.get_height()) {
        // min_cost = std::min(cost.at(row, col), min_cost);
        if(cost.at(row, col) < min_cost) {
          min_col = col;
        }
      }
      // remaining rows
      else {
        // left border
        if(min_col == 0){
          Matrix::Slice s = cost.get_row_slice(row-1, min_col, min_col+1); // middle & right col
          std::vector<int> data = s.data; // need the index of the minimum # in vector
          // if(data.at(0) <= data.at(1)){
          //   min_col = min_col;
          // }
          if(data.at(1) > data.at(0)) {
            min_col = min_col+1;
          }
        }
        // right border
        else if(min_col == cost.get_width()-1){
          Matrix::Slice s = cost.get_row_slice(row-1, min_col-1, min_col); // left & middle col
          std::vector<int> data = s.data;

          if(data.at(0) <= data.at(1)){
            min_col = min_col-1;
          }
          // else: no change
        }
        // everything else
        else{
          Matrix::Slice s = cost.get_row_slice(row-1, min_col-1, min_col+1);
          std::vector<int> data = s.data;
          // 3 values in vector, get minimum & save the index to min_col
          // // if left is min
          // if(data.at(0) <= data.at(1)){
          //   if(data.at(0) <= data.at(2)){
          //     min_col = min_col-1;
          //   }
          // }
          // // if middle is min
          // if(data.at(1) < data.at(0) && data.at(1) <= data.at(2))
          // // if right is min
          // if(data.at(2) < data.at(0) && data.at(2) < data.at(1))

          // can call min & then have for loop which has min==data.at(i), then break the loop at the first instance
          int min_data = std::min(data.at(0), std::min(data.at(1), data.at(2)));
          // q: unsigned long ?
          for(unsigned long i=0; i<data.size(); ++i){
            if(data.at(i) == min_data) {
              min_col = i;
              break;
            }
          }
        }
      }
    }
    min_vect.push_back(min_cost);
  }
  std::vector<int> reversed_vect;
  int iterator = 0;
  for(int i=min_vect.size()-1; i>=0; --i){
    reversed_vect.at(i) = min_vect.at(iterator);
    iterator++;
  }
  return reversed_vect;
}

// Returns a copy of img with the given vertical seam removed. That is, one
// pixel will be removed from every row in the image. The pixel
// removed from row r will be the one with column equal to seam[r].
// The width of the image will be one less than before.
// See the project spec for details on removing a vertical seam.
Image remove_vertical_seam(const Image& img, const std::vector<int>& seam){ 
  Image new_img = Image(img.get_width()-1, img.get_height());

  Matrix vertical_cost = compute_vertical_cost_matrix(img);
  std::vector<int> min_seam = find_minimal_vertical_seam(vertical_cost);

  for(int row=0; row<img.get_height(); ++row){
    for(int col=0; col<img.get_width(); ++col){
      // if column = a minimum col, skip column
      if(col == min_seam.at(col)) {
        col++;
      }
      // get pixel of original img & copy that into new_img
      Pixel curr_pix = img.get_pixel(row,col);
      new_img.set_pixel(row,col,curr_pix);
    }
  }
  return new_img;

}

// Returns a copy of img with its width reduced to be new_width by using
// the seam carving algorithm. See the spec for details.
// Requires that 0 < new_width <= img.get_width(), otherwise the behavior
// is undefined.
Image seam_carve_width(const Image& img, int new_width){
  Matrix energy_matrix = compute_energy_matrix(img);
  Matrix cost_matrix = compute_vertical_cost_matrix(img);
  std::vector<int> minimal_cost_seam = find_minimal_vertical_seam(cost_matrix);
  Image new_img = remove_vertical_seam(img, minimal_cost_seam);
  return new_img;
}

// Returns a copy of img with its height reduced to be new_height by using
// the seam carving algorithm. See the spec for details.
// Requires that 0 < new_height <= img.get_height(), otherwise the behavior
// is undefined.
Image seam_carve_height(const Image& img, int new_height){
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
Image seam_carve(const Image& img, int newWidth, int newHeight){
  Image new_img = seam_carve_width(img, newWidth);
  new_img = seam_carve_height(img, newHeight);
  return new_img;
}
