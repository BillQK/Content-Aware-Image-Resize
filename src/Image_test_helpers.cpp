
/* Image_test_helpers.cpp
 * Originally written by James Juett at the University of Michigan
 * for project 3 in EECS 280, Winter 2016.
 */

#include "Image_test_helpers.h"

bool Pixel_equal(Pixel p1, Pixel p2){
  return p1.r == p2.r && p1.g == p2.g && p1.b == p2.b;
}

bool Image_equal(const Image& img1, const Image& img2){
  if (img1.get_width() != img2.get_width()){ return false; }
  if (img1.get_height() != img2.get_height()){ return false; }

  for(int r = 0; r < img1.get_height(); ++r){
    for(int c = 0; c < img1.get_width(); ++c){
      if (!Pixel_equal(img1.get_pixel(r, c), img2.get_pixel(r, c))){
        return false;
      }
    }
  }

  return true;
}
