#include <fstream>
#include <iostream>

#include "Image.hpp"
#include "Matrix.hpp"
#include "processing.hpp"

using namespace std;

int main(int argc, char **argv) {
  (void)argc;
  string inputFile, outputFile;
  int width, height;

  inputFile = argv[1];
  outputFile = argv[2];
  width = stoi(argv[3]);

  if (stoi(argv[4])) {
    height = stoi(argv[4]);
  } else {
    height = 0;
  }

  cout << inputFile << " " << outputFile << " " << width << " " << height << endl;

  ifstream ifs(inputFile);

  if (!ifs.is_open()) {
    cout << "Error opening file: " << inputFile << endl;
    return 1;
  }

  Image img = Image::read_ppm(ifs);

  if ((width > img.get_width() && width < 0) 
  || (height < 0 && height > img.get_height())) {
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
         << "WIDTH and HEIGHT must be less than or equal to original" << endl;
  } else {
    Image new_img;
    if (height == 0) {
      new_img = seam_carve_width(img, width);
    } else {
      new_img = seam_carve(img, width, height);
    }
    ofstream ofs(outputFile);
    new_img.print(ofs);
  }

  return 1;
}