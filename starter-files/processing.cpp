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
  
}

// Returns the energy Matrix computed from the given Image.
// See the assignment spec for details on computing the energy matrix.
Matrix compute_energy_matrix(const Image& img) {
  Matrix energy_mat = Matrix{img.get_height(), img.get_width()};
  int max_energy;
  for(int row=1; row<energy_mat.get_height()-1; ++row) {
    for(int col=1; col<energy_mat.get_width()-1; ++col) {
      Pixel n=img.get_pixel(row-1, col);
      Pixel s=img.get_pixel(row+1, col);
      // do west east
      int energy_x = energy_mat.at(row, col) = squared_difference(n,s);
      max_energy = std::max(energy_x, max_energy);
    }
  }
  // todo: fill borders
}

// Returns the vertical cost Matrix computed from the given Image.
// See the assignment spec for details on computing the cost matrix.
Matrix compute_vertical_cost_matrix(const Image& img) {

}
// Returns a vector containing the column indices of each pixel along the
// vertical seam with the minimal cost according to the given cost matrix.
// The elements in the vector starts with the lowest numbered row (top of image)
// and progressing to the highest (bottom of image).
// While determining the seam, if any pixels tie for lowest cost, the leftmost
// one (i.e. with the lowest column number) is used.
// See the project spec for details on computing the minimal seam.
std::vector<int> find_minimal_vertical_seam(const Matrix& cost){ 

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
