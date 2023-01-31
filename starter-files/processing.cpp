#include "processing.hpp"


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
      // new_img.get_pixel(row, col) = img.get_pixel(0+col, img.get_width()-row);
      // now convert it to set_pixel
      Pixel from_pixel = img.get_pixel(0+col, img.get_width()-row);
      new_img.set_pixel(row, col, from_pixel);
    }
  }
  return new_img;

// make new image with height & width flipped
/*
pixel (0,0) top left is now at (height, 0) bottom left
(0,1) -> (height-1, 0)
the height refers to the new height
(1, 0)-> (height, 1)
(1,1)-> (height-1, 1)
(r, c)-> (r-i, c)
pixel (0, width) top right is now at (0,0) top left
pixel (height, 0) bottom left is now at (height, width) bottom right
pixel (height, width) bottom right is now at (0, width) top right
*/
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
  int max_energy;
  // fills middle
  for(int row=1; row<energy_mat.get_height()-1; ++row) {
    for(int col=1; col<energy_mat.get_width()-1; ++col) {
      Pixel n=img.get_pixel(row-1, col);
      Pixel s=img.get_pixel(row+1, col);
      Pixel w = img.get_pixel(row, col-1); 
      Pixel e = img.get_pixel(row, col+1);
      int energy_x = energy_mat.at(row, col) = squared_difference(n,s) + squared_difference(w,e);
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
        int min_energy = std::min(energy_center, energy_east);
        vertical_cost.at(row,col) += min_energy; 
      }
      // right border
      else if(col==vertical_cost.get_width()-1) {
        int energy_west = energy_mat.at(row-1,col-1);
        int energy_center = energy_mat.at(row-1,col);
        int min_energy = std::min(energy_west, energy_center);
        vertical_cost.at(row,col) += min_energy; 
      }
      // everything else
      else {
        int energy_west = energy_mat.at(row-1,col-1);
        int energy_center = energy_mat.at(row-1,col); 
        int energy_east = energy_mat.at(row-1, col+1); 
        int min_energy = std::min(energy_center, std::min(energy_west, energy_east));
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
  int min_col = 0;
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
          Matrix::Slice s = cost.get_row_slice(row-1, min_col, min_col+1);
          std::vector<int> data = s.data; // get the min
          std::min(data.at(0), data.at(1)); // this shouldnt work cause uhhh
        }
        // right border
        else if(min_col == cost.get_width()-1){
          Matrix::Slice s = cost.get_row_slice(row-1, min_col-1, min_col);
          std::vector<int> data = s.data;
          std::min(data.at(0), data.at(1));
        }
        // everything else
        else{
          Matrix::Slice s = cost.get_row_slice(row-1, min_col-1, min_col+1);
          std::vector<int> data = s.data;
          // get the minimum
        }
      }
    }
    min_vect.push_back(min_cost);
  }
}

// Returns a copy of img with the given vertical seam removed. That is, one
// pixel will be removed from every row in the image. The pixel
// removed from row r will be the one with column equal to seam[r].
// The width of the image will be one less than before.
// See the project spec for details on removing a vertical seam.
Image remove_vertical_seam(const Image& img, const std::vector<int>& seam){ 

}

// Returns a copy of img with its width reduced to be new_width by using
// the seam carving algorithm. See the spec for details.
// Requires that 0 < new_width <= img.get_width(), otherwise the behavior
// is undefined.
Image seam_carve_width(const Image& img, int new_width){

}

// Returns a copy of img with its height reduced to be new_height by using
// the seam carving algorithm. See the spec for details.
// Requires that 0 < new_height <= img.get_height(), otherwise the behavior
// is undefined.
Image seam_carve_height(const Image& img, int new_height){

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

}
